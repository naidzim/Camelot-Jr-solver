#ifndef GAMEPLAY_H
#define GAMEPLAY_H



#include <vector>
#include <iostream>
#include "tinyxml.h"
#include <aruco_msgs/MarkerArray.h>
#include <sound_play/sound_play.h>
#include "std_msgs/String.h"

#include "Piece.h"
#include "Board.h"
#include "BluePiece.h"
#include "GreenPiece.h"
#include "OrangePiece.h"
#include "PurplePiece.h"
#include "Princesse.h"
#include "Chevalier.h"
#include "RedPiece.h"



struct Coordonnes{
    int x;
    int y;
};

struct PieceCorr{
    Piece p;
    Coordonnes cor;
};

struct Cas2Piece{
    PieceCorr p1;
    PieceCorr p2;
};

struct Cas3Piece{
    PieceCorr p1;
    PieceCorr p2;
    PieceCorr p3;
};

struct Cas4Piece{
    PieceCorr p1;
    PieceCorr p2;
    PieceCorr p3;
    PieceCorr p4;
};


int toLigne(float z);
int toColonne(float y);
void xtractImage(const aruco_msgs::MarkerArray& msg, vector<Piece> &pieceDep, vector<Piece> &pieceSol);
void xtractXml(const char* xmlFileName,std::vector<Piece> &pieceDepart, std::vector<Piece> &pieceSol);
void fillBoard(Board &plateau, std::vector<Piece> const pieceDepart);
void resolutionXML(Board &plateau, std::vector<Piece> const pieceSol);
vector<Piece> resolution(Board &plateau, std::vector<Piece> const pieceSol);
int sensMouvement(Board &plateau);
int avancer(Board &plateau);
int monter(Board &plateau, int mouvDir);
int descendre(Board &plateau, int mouvDir);
int CJoinP(Board &plateau);
int testConfig(Board &plateau);
vector<Piece>* construcPossibilites(std::vector<Piece> const pieceSol);
vector<Coordonnes> slotDispo(Board &plateau);
int posable(Piece &p, Board &plateau, Coordonnes cor);
vector<Piece> etapeResolution(vector<Piece> const pieceSol);

#endif // GAMEPLAY_H