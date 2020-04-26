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
    
    if (aux.extract(s)) {
        res = true;
    }
    
    return res;
    
}

void Player::add(std::string frombag){
    assert(this->size()+frombag.size() <= MAXPLAYER);
    strcat(letters, frombag.c_str());
}

/*
bool Player::extract(const std::string s){
    bool encontrado=false;
    char copia[MAXPLAYER+1];
    strcpy(copia,letters);
    
    for(int i=0; i<s.size() && !encontrado; i++){
        int contador=0;
        
        for(int j=0; copia[j]!='\0' && !encontrado; j++){
            if(copia[j]==s[i]){
                removeCString(copia, contador);
                encontrado=true;
            }
            else
                contador++;
        }
    }
    
    if(encontrado){
        strcpy(letters,copia);
        sortCString(letters);
    }
    
    return encontrado;
    
}
*/
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
    int n = strlen(cstr);
    
    for(int i=0; i<n-2; i++){
        for(int j=i+1; j<i-1; j++){
            if(cstr[j] > cstr[i]){
                char aux = cstr[j];
                cstr[j] = cstr[i];
                cstr[i] = aux;
            }
        }
    }
}