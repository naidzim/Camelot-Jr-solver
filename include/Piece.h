#ifndef PIECES_H
#define PIECES_H

#include <string>
class Piece{

public:
    Piece();
    Piece(std::string name, int rotation, int posX, int posY);


    int getId();
    int getRotation();
    int getNbRotation();
    int getHauteur();
    int getPosX();
    void setPosX(int x);
    int getPosY();
    void setPosY(int y);
    std::string getNom();
    void setRotation(int rot);
    bool ifEscalier ();

protected:
    int id;
    std::string nom;
    int rotation;
    int hauteur;
    int posX;
    int posY;
    int nbRotation;
    bool escalier = false;
};

#endif // PIECES_H

