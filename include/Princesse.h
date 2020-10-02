#ifndef PRINCESSE
#define PRINCESSE

#include "Piece.h"

using namespace std;

class Princesse : public Piece {

public:
    Princesse();
    Princesse(std::string name,int rotation,int ligne,int colonne );

};
#endif // PRINCESSE


