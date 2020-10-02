
#include "../include/RedPiece.h"

RedPiece::RedPiece()
{
    this->id = 7;
    this->rotation = 1;
    this->hauteur = 2;
    this -> nbRotation = 3;
}

RedPiece::RedPiece(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 7;
    this->hauteur = 2;
}
