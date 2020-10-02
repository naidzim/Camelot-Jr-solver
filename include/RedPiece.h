#ifndef RED_PIECE
#define RED_PIECE

#include "Piece.h"

using namespace std;

class RedPiece : public Piece {

public:
    RedPiece();
    RedPiece(std::string name,int rotation,int ligne,int colonne );

};
#endif // RED_PIECE

