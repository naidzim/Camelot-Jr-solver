#include "../include/BluePiece.h"

BluePiece::BluePiece()
{
    this->id = 3;
    this->rotation = 2;
    this->hauteur = 2;
    this->escalier = true;
    this -> nbRotation = 6;
}

BluePiece::BluePiece(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 3;
    this->hauteur = 2;
    this->escalier = true;
    this -> nbRotation = 6;

}
