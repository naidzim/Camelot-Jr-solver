#include "../include/Princesse.h"

Princesse::Princesse()
{
    this->id = 2;
    this->rotation = 1;
    this->hauteur = 1;
}

Princesse::Princesse(std::string name,int rotation,int ligne,int colonne):
    Piece(name,rotation,ligne,colonne)
{
    this->id = 2;
    this->hauteur = 1;
}
