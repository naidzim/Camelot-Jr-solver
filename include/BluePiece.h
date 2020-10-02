#ifndef BLUE_PIECE
#define BLUE_PIECE

#include <string>

#include "Piece.h"

using namespace std;

class BluePiece : public Piece {

public:
    BluePiece();
    BluePiece(std::string name,int rotation,int ligne,int colonne );

};
#endif // BLUE_PIECE
