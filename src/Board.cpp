#include <iostream>

#include "../include/Board.h"


Board::Board()
{

}

void Board::printDebug()
{
    for (int i=0; i<4; i++)
    { std::cout << "\t" ;
        for (int j=0; j<6; j++)
        {
            switch(canvas[i][j])
            {
                case 0:
                    std::cout  << canvas[i][j]  << "  " ;
                    break;

                case 1:
                    std::cout << canvas[i][j] << "  "  ;
                    break;

                case 2:
                    std::cout << canvas[i][j] << "  "  ;
                    break;

                case 3:
                    std::cout  << canvas[i][j] << "  " ;
                    break;

                case 4:
                    std::cout  << canvas[i][j]  << "  " ;
                    break;

                case 5:
                    std::cout  << canvas[i][j] << "  "  ;
                    break;

                case 6:
                    std::cout << canvas[i][j]  << "  "  ;
                    break;

                case 7:
                    std::cout  << canvas[i][j] << "  "  ;
                    break;

                case 38:
                    std::cout << canvas[i][j] << " "  ;
                    break;

                case 83:
                    std::cout << canvas[i][j] << " "  ;
                    break;

                case 48:
                    std::cout << canvas[i][j]  << " " ;
                    break;

                case 84:
                    std::cout << canvas[i][j]  << " ";
                    break;

                default:
                    std::cout << canvas[i][j] << " ";
                    break;
            }


        }
        std::cout << "\n";
    }
    std::cout << endl;
    std::cout << "position du chevalier : " << posChevalier[0] << "," << posChevalier[1] << endl;
    std::cout << "position de la Princesse : " << posPrincesse[0] << "," << posPrincesse[1] << endl;

}

void Board::ajouterPiece(Piece p)
{
    int id = p.getId();
    int rot = p.getRotation();
    int hauteur = p.getHauteur();
    int xPos = p.getPosX();
    int yPos = p.getPosY();
    bool esca = p.ifEscalier();

    if (esca) {  // 6 rotation possible

        switch (rot){

            case 1:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos-i][yPos] = id + 92 + rot;

                    else
                        canvas[xPos-i][yPos] = id;
                }
                break;

            case 2:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos-i][yPos] = 47 + id + rot ;
                    else
                        canvas[xPos -i][yPos] = id;
                }
                break;

            case 3:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos][yPos + i] = 47 + id + rot + 1 ;
                    else
                        canvas[xPos][yPos+i] = id ;
                }
                break;

            case 4:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos][yPos + i] = 92 + id + rot;
                    else
                        canvas[xPos][yPos+i] = id;
                }
                break;

            case 5:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos][yPos-i] = 47 + id + rot + 1;
                    else
                        canvas[xPos][yPos-i] = id;
                }
                break;

            case 6:
                for (int i=0; i<hauteur; i++)
                {
                    if (i == hauteur - 1)
                        canvas[xPos][yPos-i] = 92 + id + rot ;
                    else
                        canvas[xPos][yPos-i] = id;
                }
                break;

            default:
                break;
        }
    }

    else // 3 rotation possible
    {
        switch (rot){

            case 1:
                for (int i=0; i<hauteur; i++)
                {
                    canvas[xPos-i][yPos] = id;
                }
                break;

            case 2:
                for (int i=0; i<hauteur; i++)
                {
                    canvas[xPos][yPos+i] = id;
                }
                break;

            case 3:
                for (int i=0; i<hauteur; i++)
                {
                    canvas[xPos][yPos-i] = id;
                }
                break;

            default:
                break;
        }
    }

    if (id == 1 ) // c'est un chevalier
    {
        posChevalier [0] = xPos;
        posChevalier[1] = yPos;
    }
    if (id == 2 ) // c'est un chevalier
    {
        posPrincesse [0] = xPos;
        posPrincesse [1] = yPos;
    }
}

const int* Board::getPosChevalier()
{

    return posChevalier;
}

const int* Board::getPosPrincesse()
{

    return posPrincesse;
}

void Board::setPosChevalier(int xPos, int yPos)
{
    posChevalier[0] = xPos;
    posChevalier[1] = yPos;
}

const int Board::getElem(int xPos,int yPos)
{
    int x = xPos;
    int y = yPos;

    if (xPos >= 3)
        x = 3;
    if (yPos >= 5)
        y = 5;

    return canvas[x][y];
}

void Board::setElem(int id, int xPos, int yPos)
{
    canvas[xPos][yPos] = id;
}

void Board::print()
{
    for (int i=0; i<4; i++)
    { std::cout << "\t" ;
        for (int j=0; j<6; j++)
        {

            if(canvas[i][j] == 0)
            {
                std::cout  << canvas[i][j]  << "  "  ;
            }
            if(canvas[i][j] == 1)
            {

                std::cout << "C" << "  "  ;
            }

            if(canvas[i][j] == 2)
            {
                std::cout  << "P" << "  " ;
            }

            if(canvas[i][j] == 3)
            {
                std::cout <<  char(254)  << "  "  ;
            }

            if(canvas[i][j] == 4)
            {
                std::cout << char(254)  << "  "  ;
            }

            if(canvas[i][j] == 5)
            {
                std::cout  << char(254)  << "  "  ;
            }
            if(canvas[i][j] == 6)
            {
                std::cout  << char(254)  << "  " ;
            }
            if(canvas[i][j] == 7)
            {
                std::cout << char(254)  << "  "  ;
            }
            if(canvas[i][j] == 52 )
            {
                std::cout  << char(47) << "  "  ;
            }
            if(canvas[i][j] == 53 )
            {
                std::cout << char(47) << "  "  ;
            }
            if(canvas[i][j] == 54 )
            {
                std::cout  << char(47) << "  "  ;
            }
            if(canvas[i][j] == 55 )
            {
                std::cout << char(47) << "  "  ;
            }
            if(canvas[i][j] == 56 )
            {
                std::cout  << char(47) << "  "  ;
            }
            if(canvas[i][j] == 57 )
            {
                std::cout  << char(47) << "  "  ;
            }
            if(canvas[i][j] == 96 )
            {
                std::cout  << char(92) << "  "  ;
            }
            if(canvas[i][j] == 97 )
            {
                std::cout  << char(92) << "  "  ;
            }
            if(canvas[i][j] == 99 )
            {
                std::cout  << char(92) << "  "  ;
            }
            if(canvas[i][j] == 100 )
            {
                std::cout << char(92) << "  "  ;
            }
            if(canvas[i][j] == 101 )
            {
                std::cout  << char(92) << "  "  ;
            }
            if(canvas[i][j] == 102 )
            {
                std::cout << char(92) << "  "  ;
            }


            if(canvas[i][j] == 12 )
            {
                std::cout << "PC" << " "  ;
            }

        }
        std::cout << "\n";
    }
    std::cout << endl;
    std::cout << "position du chevalier : " << posChevalier[0] << "," << posChevalier[1] << endl;
    std::cout << "position de la Princesse : " << posPrincesse[0] << "," << posPrincesse[1] << endl;

}
