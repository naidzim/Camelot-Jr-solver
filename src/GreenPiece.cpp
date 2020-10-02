#include "../include/GreenPiece.h"

GreenPiece::GreenPiece()
{
    this->id = 4;
    this->rotation = 1;
    this->hauteur = 3;
    this->escalier = true;
    this -> nbRotation = 6;
}

GreenPiece::GreenPiece(std::string name,int rotation,int ligne,int colonne ):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 4;
    this->hauteur = 3;
    this->escalier = true;
    this -> nbRotation = 6;
}
