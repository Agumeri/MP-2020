/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>
#include <iostream>
#include <fstream>
#include "player.h"
#include "language.h"
#include "move.h"
using namespace std;

Move::Move()  {
    row = 0;
    column = 0;
    ishorizontal = true;
    letters = "";
    score = 0;
}

void Move::set(int r, int c, char h, const std::string &l) {
    setRow(r);
    setCol(c);
    setHorizontal(h);
    setLetters(l);
}

void Move::setRow(int r) {
    row = r;
}

void Move::setCol(int c){
    column = c;
}

void Move::setHorizontal(char h){
    if(h == 'H' || h == 'h'){
        ishorizontal = true;
    }else if(h == 'V' || h == 'v'){
        ishorizontal = false;
    }
}

void Move::setLetters(const std::string &l) {
    letters = normalizeWord(l);
}

int Move::findScore(const Language &l) const{
    int aux = 0;
    for(int i=0; i<letters.size(); i++){
        aux += l.getScore(letters[i]);
    }
    
    if(aux>0)
        return aux;
    else
        return -1;
}

void Move::setScore(int s){
    this->score = s;
}

int Move::getScore() const{
    return this->score;
}

int Move::getRow() const{
    return this->row;
}

int Move::getCol() const{
    return this->column;
}

bool Move::isHorizontal() const{
    return this->ishorizontal;
}

std::string Move::getLetters() const{
    return this->letters;
}

void Move::print(std::ostream &os) const{
    os << "READ: ";
    
    if(isHorizontal())
        os << "H ";
    else
        os << "V ";
    
    os << row << " " << column << " " << letters << " ";
    
    
}

void Move::read(std::istream &is) {
    int n_r, n_c;
    char horz;
    std::string palabra;
    //@warging reading
    is >> horz;
    is >> n_r;
    is >> n_c;
    is >> palabra;

    set(n_r, n_c, horz, palabra);
}