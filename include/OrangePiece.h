#ifndef ORANGE_PIECE
#define ORANGE_PIECE

#include "Piece.h"

using namespace std;

class OrangePiece : public Piece {

public:
    OrangePiece();
    OrangePiece(std::string name,int rotation,int ligne,int colonne);

};
#endif // ORANGE_PIECE

