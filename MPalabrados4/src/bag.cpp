/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <cassert>
#include <random>
#include <string>
#include <algorithm>
#include "bag.h"
///@warning Fill missing #include

using namespace std;

/**
 * @brief Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 */
void removeVector(char *s, int &n, int p);


// Main methods

Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

///@warning Implement all the methods

// Auxiliary functions 
char Bag::get(int p)const{
    assert(p>=0 && p<nletters);
    
    return letters[p];    
}

void Bag::set(int p, char c){
    assert(p>=0 && p<nletters);
    
    letters[p]=c;
}

void Bag::setRandom(int _id){
    id=_id;
}

void Bag::define(const Language &l){
    string forletters = l.getLetterSet();
    nletters = 0;
    for (int i = 0; i < forletters.size(); i++)
        nletters += l.getFrequency(forletters[i]);  
    assert(nletters <= MAXBAG); // para comprobar que hay espacio en el vector, sino excepción!
    for (int k = 0, i = 0; i < forletters.size(); i++)
        for (int j = 0; j < l.getFrequency(forletters[i]); j++)
            set(k++,(forletters[i]));
    shuffleVector(letters, nletters, id);

}

int Bag::size() const{
    return nletters;
}

std::string Bag::to_string() const{
    string s(nletters,'-');
    for (int i=0;i <nletters; i++)
        s[i]=get(i);
    return s;
}

void Bag::set(std::string s){
    assert(s.size() <= MAXBAG);
    
    nletters=s.size();
    for(int i=0; i<s.size();i++){
        letters[i]= s[i];
    }
}

std::string Bag::extract(int n){
    string result="";
    if (n > nletters)
        n = nletters;
    for (int i=0; i<n; i++) {
        result.append(1,get(0));
        removeVector(letters, nletters, 0);
    }
    return result;

}

void shuffleVector(char *s, int n, int id) {
    vector <char> aux(s, s+n);
    unsigned seed = id;
    std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed));
    for (int i=0; i<n; i++)
        s[i] = aux[i];    
}

void removeVector(char *s, int &n, int p){
    assert(p>=0 && p<n);
    
    for(int i=p; i<n-1; i++){
        s[i]=s[i+1];        
    }
    n=n-1;
}