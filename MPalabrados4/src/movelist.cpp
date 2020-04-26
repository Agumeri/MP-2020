/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>
#include <cassert>
#include "movelist.h"

using namespace std;


//Metodos privados de la clase Movelist

void Movelist::allocate(int n){
    assert(n>=0);
    moves = new Move[n];
    nMove = n;
}

void Movelist::deallocate(){
    delete[] moves;
    moves = nullptr;
    nMove = 0;
}

void Movelist::copy(const Movelist &ml){
    this->deallocate();
    this->allocate(ml.size());
    for(int i=0; i<nMove; i++)
        set(i,ml.get(i));
}

//Move m1 ---> | a |
//     m2 --------> | a | b | c |
//
//m1.copy(m2);
//¿m1 == m2?  ----> m1.operator==(m2);

//Metodos publicos de la clase Movelist

Movelist::Movelist(){
    this->allocate(0);
}

Movelist::Movelist(int nmov){
    moves=nullptr;
    this->allocate(nmov);
}

Movelist::Movelist(const Movelist &orig){
    allocate(orig.nMove);
    this->moves = orig.moves;
    
}

Movelist::~Movelist(){
    this->deallocate();
}

void Movelist::assign(const Movelist& orig){
    this->copy(orig);
}

Move Movelist::get(int p) const{
    assert(p>=0 && p<nMove);
    return this->moves[p];
}

void Movelist::set(int p, Move m){
    assert(p>=0 && p<nMove);
    moves[p] = m;
}

int Movelist::size() const{
    return this->nMove;
}

int Movelist::find(Move mov){
    int pos = -1;
    bool encontrado = false;
    Move aux;
    
    for(int i=0; i<this->nMove && !encontrado; i++){
        aux = moves[i];
        
        //Condicion necesaria para que un movimiento sea igual a otro. ¿Cambiar por sobrecarga de operador ==?
        if(aux.esIgual(mov))
        {
            pos = i;
            encontrado = true;
        }
    }
    
    return pos;
}

void Movelist::add(const Move &mov){
    Movelist aux(nMove+1);
    
    for(int i=0; i<nMove; i++)
        aux.moves[i] = moves[i];
    
    aux.set(nMove,mov);
    this->copy(aux);
    
}

void Movelist::remove(Move mov){
    Movelist aux;
    Move m_aux;
    
    for (int i = 0; i<nMove; i++) {
        m_aux = this->get(i);
        if(!m_aux.esIgual(mov)){
            aux.add(m_aux);
        }
    }
    
    this->copy(aux);
    
    
}

void Movelist::removePos(int p){
    assert(p>=0 && p<nMove);
    Move aux = this->moves[p];
    this->remove(aux);
}

void Movelist::zip(const Language& l){
    Move aux;
    
    for(int i=0; i<this->nMove; i++){
        aux = this->moves[i];
        if(aux.getLetters().size() < 2 || l.query(aux.getLetters())){
            this->remove(aux);
        }
    }
}

void Movelist::clear(){
    this->deallocate();
    this->allocate(0);
}

double Movelist::getScore() const{
    double puntuacion= 0.0;
    
    for(int i=0; i<this->nMove; i++){
        puntuacion += this->moves[i].getScore();
    }
    
    return puntuacion;
}

bool Movelist::print(std::ostream &os, bool scores) const {
    bool res=true;
    for (int i=0; i<nMove && res; i++) {
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

bool Movelist::read(std::istream& is){
    Move aux;
    bool res = true;
    
    aux.read(is);
    
    while(aux.getLetters() != "@" && aux.getLetters() != "_" && !is.eof()){
        this->add(aux);
        aux.read(is);
    }
    
    if(is.eof() || this->get(nMove-1).getLetters() == "_"){
        res = false;
    }
    
    return res;
}