/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <iostream>
#include <cstring>
#include <cassert>
#include <string>
#include "player.h"
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos);

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr);

Player::Player(){
    clear();
}

int Player::size() const{
    return strlen(letters);
}

std::string Player::to_string() const{
    string res(letters);
    return res;
}

void Player::clear(){
    letters[0] = '\0';
}

bool Player::isValid(const std::string s) const{
    bool res = false;
    Player aux = *this;
    
    if (s.length()>0 && aux.extract(s)) {
        res = true;
    }
    
    return res;
    
}

void Player::add(std::string frombag){
    string s(frombag);
    int nSize = MAXPLAYER - size();
    if(frombag.size() > nSize)
        s = s.substr(0,nSize);
    strcat(letters, frombag.c_str());
    sortCString(letters);
}

bool Player::extract(const std::string s){
    bool continuar = true, encontrado = false;
    
    char aux[MAXPLAYER+1];
    strcpy(aux,letters);
    
    for(int i=0; i<s.size() && continuar; i++){
        char c = s[i];
        int j=0;
        while(j<strlen(aux) && !encontrado){
            if(aux[j] == c){
                removeCString(aux,j);
                encontrado = true;
            }else{
                j++;
            }
        }
        if(!encontrado){
            continuar = false;
        }
        encontrado = false;
    }
    
    if (continuar){
        strcpy(letters,aux);
        sortCString(letters);
    }
    
    return continuar;
}

void removeCString(char *cstr, int pos){
    assert(pos>=0 && pos<strlen(cstr));
    
    for(int i=pos; i<strlen(cstr); i++){
        cstr[i]=cstr[i+1];
    }
    
}

void sortCString(char *cstr){
    int lowest;
    for (int i=0; i<strlen(cstr); i++) {
        lowest = i;
        for(int j=i; j<strlen(cstr); j++)
            if (cstr[j] < cstr[lowest])
                lowest = j;
        if (lowest != i) {
            char aux = cstr[i];
            cstr[i] = cstr[lowest];
            cstr[lowest] = aux;
        }
    }
}