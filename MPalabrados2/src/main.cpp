/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <iostream>
#include "mi_random.h"
#include "language.h"
#include "bag.h"
#include "player.h"
///@warning complete missing #includes

using namespace std;
/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of letters found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    int Id;             /// To be used in bag.setRandom())
    Bag bag;            /// Bag of letters
    Player player;      /// Player set of letters
    string lang;  /// Language to be loaded from disk
    string result, palabra;     /// String that contains all the words found
    int nletters,          /// Number of letters found
        nwords;          /// Number of words found
    bool extraer = false, rendirse = false;
    
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    Language language(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "TYPE SEED (<0 RANDOM): ";
    cin >> Id;
    
    bag.setRandom(Id);
    bag.define(language);
    player.add(bag.extract(7));
    
    cout << "BAG ("<<bag.size()<<") : "<<toUTF(bag.to_string())<< endl;
    
    cout << "-----COMIENZA EL JUEGO-----(Escribe rendirse para terminar)" << endl;
    while(bag.size()>0 && !rendirse){
        cout << "\nPLAYER: "<< toUTF(player.to_string()) << " BAG(" <<bag.size() << ")" << endl;
        cout << "\nEscribe una palabra posible: " ;
        cin >> palabra;
        
        if(palabra != "rendirse"){ 
            if(player.isValid(palabra)){
                if(language.query(palabra)){
                    cout << palabra << " es una palabra valida, y se ha extraido,continua con el juego" << endl;
                    nwords++;
                    result += palabra+"-";
                    extraer = true;
                }
                if(extraer){
                    player.extract(palabra);
                    player.add(bag.extract(7-player.size()));
                    extraer = false;
                }
            }
        }else{
            rendirse = true;
        }
        
    }
    
    cout << "\n-----FIN DEL JUEGO-----" << endl;
    cout << "R E S U L T A D O S" << endl;
    HallOfFame(language,Id,bag,player, nwords, nletters, result);
    return 0;
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " letters "<<endl << 
            toUTF(result) << endl;    
}