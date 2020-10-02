#ifndef CHEVALIER_H
#define CHEVALIER_H

#include "Piece.h"

using namespace std;

class Chevalier : public Piece {

public:
    Chevalier();
    Chevalier(std::string name,int rotation,int ligne,int colonne );

};
#endif // CHEVALIER_H
