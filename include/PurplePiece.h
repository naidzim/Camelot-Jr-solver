
#ifndef PURPLE_PIECE
#define PURPLE_PIECE

#include "Piece.h"

using namespace std;

class PurplePiece : public Piece {

public:
    PurplePiece();
    PurplePiece(std::string name,int rotation,int ligne,int colonne);

};
#endif // PURPLE_PIECE

