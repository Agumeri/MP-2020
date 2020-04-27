/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */


#include <iostream>
#include <string>
#include "language.h"
#include "bag.h"
#include "mi_random.h"
#include "move.h"
#include "player.h"
#include "movelist.h"

using namespace std;

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo);

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);

int main(int argc, char * argv[]) {
    Movelist movements, /// Original list of movements
            legalmovements, /// Movements with legal words upon the dictionary
            acceptedmovements,/// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    string bolsa = "";
    std::string lang = "", ifilename = "", ofilename = "";
    int random = -1, nwords = 0, score = 0;
    ifstream ifile;
    ofstream ofile;
    istream *input;
    ostream *output;

    //./mpalabrados3 -l ES -i archivo.dat -r 16
    //version inicial de lectura de parametros. ¿Bien o mal? ¿Dentro de metodo istream?
    if(argv[1] != "<"){
        for (int i = 0; i < argc; i++) {
            string aux = "";
            aux += argv[i];

            if (aux == "-l") {
                if (i + 1 >= argc) errorBreak(ERROR_ARGUMENTS, "");
                lang = argv[i + 1];
                i++;
            } else if (aux == "-p") {
                if (i + 1 >= argc) errorBreak(ERROR_ARGUMENTS, "");
                ifilename = argv[i + 1];
                i++;
            } else if (aux == "-r") {
                if (i + 1 >= argc) errorBreak(ERROR_ARGUMENTS, "");
                random = atoi(argv[i + 1]);
                i++;
            } else if (aux == "-b") {
                if (i + 1 >= argc) errorBreak(ERROR_ARGUMENTS, "");
                bolsa = argv[i + 1];
                i++;
            }
        }
    }

    //Si lang está vacío, muestra erro al no haber introducido el parametro obligatorio
    if (lang == "" || ifilename == "") {
        errorBreak(ERROR_ARGUMENTS, "");
    }

    //Creamos instancia del lenguaje con el ID obtenido
    Language language(lang);
    cout << "LANGUAGE: " << language.getLanguage() << endl;
    
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) << endl;

    if (random > -1) {
        cout << "SEED: " << random << endl;
    }
    
    //Creamos instancia de la clase bag e inicializamos el generador de numeros aleatorios
    Bag bag;

    if (bolsa != "") {
        bag.set(toISO(bolsa));
    } else {
        bag.define(language);
    }
    bag.setRandom(random);

    cout << "BAG (" << bag.size() << ") : " << toUTF(bag.to_string()) << endl;

    //Creamos la instancia de la clase player y la llenamos con caracteres de la bolsa (hasta el maximo posible)
    Player player;
    Move move;
    int puntuacion=0;
    player.add(bag.extract(7));
    
    //Lectura del fichero de movimientos guardados
    /***********************************************************/
    if (ifilename == "") {
        input = &cin;
    } else {
        ifile.open(ifilename);
        if (!ifile) {
            errorBreak(ERROR_OPEN, ifilename);
        }
        input = &ifile;
        if (!movements.read(*input)) {
            errorBreak(ERROR_DATA, ifilename);
        }
        cout << "Reading from " << ifilename << endl;

        
    }
    /***********************************************************/
    
    //Asignar movimientos al resto de movelist (legal, accepted, rejected)
    /***********************************************************/
    legalmovements.assign(movements);
  
    legalmovements.zip(language);

    for (int i = 0; i < legalmovements.size(); i++) {
        cout << "\nPLAYER: " << player.to_string() << endl;
        
        move = legalmovements.get(i);
        
        if (player.isValid(move.getLetters())) {
            //Obtenemos la puntuacion y se la asignamos al objeto 
            //move que vamos a introducir en acceptedmovements
            puntuacion = move.findScore(language);
            move.setScore(puntuacion);
            acceptedmovements.add(move);

            //Extraemos el contenido de player e introducimos nuevas letras
            player.extract(move.getLetters());
            player.add(bag.extract(7 - player.size()));

            //Mostramos por pantalla la información movimiento encontrado valido
            cout << "MOVEMENT: ";
            move.print(cout);
            cout << " FOUND!" << " " << move.getScore() << endl;
        } else {
            cout << "MOVEMENT: ";
            move.print(cout);
            cout << " INVALID!" << endl;
            
            rejectedmovements.add(move);
        }
         
    }
    /***********************************************************/

    
    if (input->eof())
        errorBreak(ERROR_DATA, ifilename);

    ifile.close();
    
    HallOfFame (language, random, bag, player, 
            movements, legalmovements, acceptedmovements, rejectedmovements);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string());
    cout << endl << endl << "ORIGINAL ("<<original.size()<<"): "<<endl; original.print(cout);
    cout << endl << endl << "LEGAL ("<<legal.size()<<"): "<<endl; legal.print(cout);
    cout << endl << endl << "ACCEPTED ("<<accepted.size()<<") SCORE "<<accepted.getScore()<< ": "<<endl; accepted.print(cout);
    cout << endl << endl << "REJECTED ("<<rejected.size()<<"): "<<endl; rejected.print(cout);
    cout << endl;
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>]"<<endl;
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}