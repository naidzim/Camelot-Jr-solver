#include "../include/OrangePiece.h"

OrangePiece::OrangePiece()
{
    this->id = 5;
    this->rotation = 1;
    this->hauteur = 1;
    this -> nbRotation = 1;
}

OrangePiece::OrangePiece(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 5;
    this->hauteur = 1;
}
