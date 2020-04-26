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
 * @param nwords Number of words found
 * @param score Number of points scored
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);


/**
 * @brief Main function. 
 * @return 
 */
int main(int argc, char * argv[]) {
    string bolsa = "";
    std::string word, lang="", goodmoves="", badmoves="", ifilename="", ofilename="";
    int random=-1, nwords=0, score=0;
    ifstream ifile; ofstream ofile;
    istream *input; ostream *output;
    
    //Filtro que muestra un mensaje de error si los argumentos no se han introducido correctamente
    if(argc<3 || argc>9){
        cerr << "Formato: [OBLIGATORIO] -l <ID> [OPCIONALES]: -i <file> -r <random> -b <secuenciacaracteres>" << endl;
        return -1;
    }
    
    
    //./mpalabrados3 -l ES -i archivo.dat -r 16
    //version inicial de lectura de parametros. ¿Bien o mal? ¿Dentro de metodo istream?
    for(int i=1; i<argc; i++){
        string aux = "";
        aux += argv[i];
        
        if(aux == "-l"){
            if(i+1 >= argc) errorBreak(ERROR_ARGUMENTS,"");
            lang = argv[i+1];
            i++;
        }else if(aux == "-i"){
            if(i+1 >= argc) errorBreak(ERROR_ARGUMENTS,"");
            ifilename = argv[i+1];
            i++;
        }else if(aux == "-r"){
            if(i+1 >= argc) errorBreak(ERROR_ARGUMENTS,"");
            random = atoi(argv[i+1]);
            i++;
        }else if(aux == "-b"){
            if(i+1 >= argc) errorBreak(ERROR_ARGUMENTS,"");
            bolsa = argv[i+1];
            i++;
        }else{
            errorBreak(ERROR_ARGUMENTS,"");
        }
            
    }
    
    //Si lang está vacío, muestra erro al no haber introducido el parametro obligatorio
    if(lang == ""){
        errorBreak(ERROR_ARGUMENTS,"");
    }
    
    //Creamos instancia del lenguaje con el ID obtenido
    Language language(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    
    //Creamos instancia de la clase bag e inicializamos el generador de numeros aleatorios
    Bag bag;
    
    if (bolsa != "") {
        bag.set(toISO(bolsa));
    } else {
        bag.define(language);
        if (random > -1) {
            cout << "SEED: " << random << endl;
        } else {
            do {
                cout << "TYPE SEED (<0 RANDOM): ";
                cin >> random;
            } while (random <= -1);
        }
    }
    bag.setRandom(random);
    
    cout << "BAG (" << bag.size() << ") : " << bag.to_string() << endl;
    
    //Creamos la instancia de la clase player y la llenamos con caracteres de la bolsa (hasta el maximo posible)
    Player player;
    Move move;
    bool condicion = false;
    player.add(bag.extract(7));
    cout << "PLAYER: " << player.to_string() << endl;
    
    if (ifilename == "") {
        input = &cin;
    } else {
        ifile.open(ifilename);
        if(!ifile){
            errorBreak(ERROR_OPEN,ifilename);
        }
        input = &ifile;
        cout << "Reading from " << ifilename << endl;
    }

    move.read(*input);
    word = move.getLetters();

    while (word.size() > 1 && bag.size() > 0) {
        //condicion = player.isValid(move.getLetters());
        condicion = language.query(move.getLetters());
        

        if (!condicion) {
            move.print(cout);
            cout << "NOT REGISTERED!" << endl;
            player.clear();
            player.add(bag.extract(7));
        } else {
            if (!player.isValid(move.getLetters())) {
                move.print(cout);
                cout << " INVALID!" << endl;
            } else {
                score += move.findScore(language);
                move.print(cout);
                cout << " FOUND!     " << move.findScore(language) << " POINTS!!!" << endl;
                player.extract(move.getLetters());
                player.add(bag.extract(7 - player.size()));
                nwords++;
                goodmoves += move.getLetters() + " - ";
            }
        }
        //Comprobar condicion final
        cout << "PLAYER: " << toUTF(player.to_string()) << endl;
        move.read(*input);
        word = move.getLetters();
    }
    
    if(input->eof())
        errorBreak(ERROR_DATA,ifilename);

        
    
    HallOfFame(language, random, bag, player, nwords, score, goodmoves);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " points "<<endl << 
            toUTF(result) << endl;    
}

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language>  [-r <randomnumber> -i <inputfile>]"<<endl;
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
