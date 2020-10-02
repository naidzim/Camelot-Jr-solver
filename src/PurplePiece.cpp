#include "../include/PurplePiece.h"

PurplePiece::PurplePiece()
{
    this->id = 6;
    this->rotation = 1;
    this->hauteur = 1;
    this -> nbRotation = 1;
}
PurplePiece::PurplePiece(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 6;
    this->hauteur = 1;
    this -> nbRotation = 1;
}

