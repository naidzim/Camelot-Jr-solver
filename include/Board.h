#ifndef BOARD_H
#define BOARD_H

#include <string>

#include "BluePiece.h"
#include "Piece.h"
#include "ConsolePrint.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
namespace con = JadedHoboConsole;
#else

#endif

class Board{

public:
    Board();
    void print();
    void printDebug();
    void ajouterPiece(Piece p); // ajoute une piece dans le canvas
    const int* getPosChevalier(); // coodonnes du chevalier
    const int* getPosPrincesse(); // coordonnes de la princess
    void setPosChevalier(int xPos, int yPos);
    const int getElem(int xPos,int yPos); // return l'id de la position choisie
    void setElem(int id, int xPos, int yPos);

protected:
    int canvas[4][6] =
        {{0,0,0,0,0,0},
         {0,0,0,0,0,0},
         {0,0,0,0,0,0},
         {0,0,0,0,0,0}
        };


    int posChevalier [2] = {-1,-1};
    int posPrincesse [2] = {-1,-1};
};
#endif // BOARD
