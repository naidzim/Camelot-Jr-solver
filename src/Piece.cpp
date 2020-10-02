#include "../include/Piece.h"

using namespace std ;

Piece::Piece()
{

}

Piece::Piece(std::string name, int rotation, int posX, int posY)
{
    this->nom = name;
    this->rotation = rotation;
    this->posX = posX;
    this->posY = posY;
}


int Piece::getId()
{
    return id;
}

int Piece::getRotation()
{
    return rotation;
}

int Piece::getNbRotation()
{
    return nbRotation;
}

int Piece::getHauteur()
{
    return hauteur;
}
int Piece::getPosX()
{
    return posX;
}

void Piece::setPosX(int x)
{
    posX = x;
}

int Piece::getPosY()
{
    return posY;
}

void Piece::setPosY(int y)
{
    posY = y;
}
std::string Piece::getNom()
{
    return nom;
}

void Piece::setRotation(int rot)
{
    rotation = rot;
}

bool Piece::ifEscalier()
{

    return escalier;
}
