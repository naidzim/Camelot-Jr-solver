#ifndef GREEN_PIECE
#define GREEN_PIECE

#include "Piece.h"

using namespace std;

class GreenPiece : public Piece {

public:
    GreenPiece();
    GreenPiece(std::string name,int rotation,int ligne,int colonne);

};
#endif // GREEN_PIECE

