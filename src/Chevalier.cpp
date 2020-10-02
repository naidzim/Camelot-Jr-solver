#include "../include/Chevalier.h"

Chevalier::Chevalier()
{
    this->id = 1;
    this->rotation = 1;
    this->hauteur = 1;
}


Chevalier::Chevalier(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 1;
    this->hauteur = 1;
}
