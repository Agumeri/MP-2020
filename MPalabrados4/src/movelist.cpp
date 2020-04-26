/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>
#include "Movelist"

using namespace std;


bool Movelist::print(std::ostream &os, bool scores) const {
    bool res=true;
    for (int i=0; i<size() && res; i++) {
        get(i).print(os);
        if (scores)
            os << " ("<<get(i).getScore()<<") - ";
        else
            os << " - ";
        if (os.bad())
            res=false;
    }
    return res;
}

Movelist::Movelist(){
    moves=nullptr;
    nMove=0;
}

Movelist::Movelist(nmov){
    moves=nullptr;
    nMoves=nmov;
}

Movelist::Movelist(orig){
    
}