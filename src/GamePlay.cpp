#include "../include/GamePlay.h"


using namespace std;



/*Global variables */

//Piece ID from config.xml file
int CIDmax, CIDmin; //chevalier
int PIDmax, PIDmin; // princesse
int OP1IDmax, OP1IDmin; // Orange 1
int OP2IDmax, OP2IDmin; // Orange 2
int R1IDmax, R1IDmin; // Red 1
int R2IDmax, R2IDmin; // Red 2
int PuIDmax, PuIDmin; // purple
int GIDmax, GIDmin; // Green
int B1IDmax, B1IDmin; // Blue 1
int B2IDmax, B2IDmin; // Blue 2
int SocleID; // socle

//rotations y axis range
double R12Ymin, R12Ymax, R34Ymin, R34Ymax, R56Ymin, R56Ymax;

//bord du socle
double SXmin, SXmax, SYmin, SYmax;

//lignes et colonnes delimitations
double l0min, l0max, l1min, l1max, l2min, l2max, l3min, l3max;
double c0min, c0max, c1min, c1max, c2min, c2max, c3min, c3max, c4min, c4max, c5min, c5max;

int GRotPaire, GRotImpaire;
int B1RotPaire, B1RotImpaire;
int B2RotPaire, B2RotImpaire;



void configXml(const char* xmlFileName)
{
    //char* xmlFileName = "solution/solution1.xml";
    TiXmlDocument XMLdoc(xmlFileName);
    bool loadOkay = XMLdoc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *pConfig, *pPiece, *pSocle, *pNom, *pID, *pRot;
        string nom;
        pConfig = XMLdoc.FirstChildElement( "config" );
        if (pConfig)
        {
            pPiece = pConfig->FirstChildElement("piece");
            while (pPiece)
            {
                pNom = pPiece->FirstChildElement("nom");
                nom = pNom->Attribute("nom");
                //pID = pPiece-> FirstChildElement("id");
                if (nom == "CHEVALIER")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&CIDmin);
                    pID->Attribute("idmax",&CIDmax);

                }
                else if (nom == "Princess")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&PIDmin);
                    pID->Attribute("idmax",&PIDmax);

                }
                else if (nom == "orange piece 1")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&OP1IDmin);
                    pID->Attribute("idmax",&OP1IDmax);

                }
                else if (nom == "orange piece 2")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&OP2IDmin);
                    pID->Attribute("idmax",&OP2IDmax);

                }
                else if (nom == "purple piece")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&PuIDmin);
                    pID->Attribute("idmax",&PuIDmax);

                }
                else if (nom == "red piece 1")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&R1IDmin);
                    pID->Attribute("idmax",&R1IDmax);

                }
                else if (nom == "red piece 2")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&R2IDmin);
                    pID->Attribute("idmax",&R2IDmax);

                }
                else if (nom == "green piece")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&GIDmin);
                    pID->Attribute("idmax",&GIDmax);
                    pRot = pPiece -> FirstChildElement("rotation1");
                    pRot->Attribute("id",&GRotImpaire);
                    pRot->Attribute("ymin",&R12Ymin);
                    pRot->Attribute("ymax",&R12Ymax);
                    pRot = pPiece -> FirstChildElement("rotation2");
                    pRot->Attribute("id",&GRotPaire);
                    pRot = pPiece -> FirstChildElement("rotation3");
                    pRot->Attribute("ymin",&R34Ymin);
                    pRot->Attribute("ymax",&R34Ymax);
                    pRot = pPiece -> FirstChildElement("rotation5");
                    pRot->Attribute("ymin",&R56Ymin);
                    pRot->Attribute("ymax",&R56Ymax);



                }
                else if (nom == "blue piece 1")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&B1IDmin);
                    pID->Attribute("idmax",&B1IDmax);
                    pRot = pPiece -> FirstChildElement("rotation1");
                    pRot->Attribute("id",&B1RotImpaire);
                    pRot = pPiece -> FirstChildElement("rotation2");
                    pRot->Attribute("id",&B1RotPaire);

                }
                else if (nom == "blue piece 2")
                {
                    pID = pPiece-> FirstChildElement("id");
                    pID->Attribute("idmin",&B2IDmin);
                    pID->Attribute("idmax",&B2IDmax);
                    pRot = pPiece -> FirstChildElement("rotation1");
                    pRot->Attribute("id",&B2RotImpaire);
                    pRot = pPiece -> FirstChildElement("rotation2");
                    pRot->Attribute("id",&B2RotPaire);

                }

                pPiece = pPiece->NextSiblingElement( "piece" );

            }
            pSocle = pConfig->FirstChildElement("socle");
            pID = pSocle-> FirstChildElement("id");
            pID->Attribute("id",&SocleID);
            pID = pSocle-> FirstChildElement("x");
            pID->Attribute("xmin", &SXmin);
            pID->Attribute("xmax", &SXmax);
            pID = pSocle-> FirstChildElement("y");
            pID->Attribute("ymin", &SYmin);
            pID->Attribute("ymax", &SYmax);
            pID = pSocle-> FirstChildElement("l0");
            pID->Attribute("zmin", &l0min);
            pID->Attribute("zmax", &l0max);
            pID = pSocle-> FirstChildElement("l1");
            pID->Attribute("zmin", &l1min);
            pID->Attribute("zmax", &l1max);
            pID = pSocle-> FirstChildElement("l2");
            pID->Attribute("zmin", &l2min);
            pID->Attribute("zmax", &l2max);
            pID = pSocle-> FirstChildElement("l3");
            pID->Attribute("zmin", &l3min);
            pID->Attribute("zmax", &l3max);
            pID = pSocle-> FirstChildElement("c0");
            pID->Attribute("ymin", &c0min);
            pID->Attribute("ymax", &c0max);
            pID = pSocle-> FirstChildElement("c1");
            pID->Attribute("ymin", &c1min);
            pID->Attribute("ymax", &c1max);
            pID = pSocle-> FirstChildElement("c2");
            pID->Attribute("ymin", &c2min);
            pID->Attribute("ymax", &c2max);
            pID = pSocle-> FirstChildElement("c3");
            pID->Attribute("ymin", &c3min);
            pID->Attribute("ymax", &c3max);
            pID = pSocle-> FirstChildElement("c4");
            pID->Attribute("ymin", &c4min);
            pID->Attribute("ymax", &c4max);
            pID = pSocle-> FirstChildElement("c5");
            pID->Attribute("ymin", &c5min);
            pID->Attribute("ymax", &c5max);
            
        }
    }
    else
    {
        cout << endl;
        cerr << "**** Error : Cannot find xml config file ****" << endl;
        cout << endl;
    }
}



bool operator!=(Coordonnes const& cor1, Coordonnes const& cor2)
{
    if (cor1.x == cor2.x && cor1.y == cor2.y)
    {
        return false;
    }
    return true;
}


int toLigne(float z)
{
    if (z>=l3min && z <= l3max)
    {
        return 3;
    }
    else if (z>=l2min && z <= l2max)
    {
        return 2;
    }
    else if (z>=l1min && z <= l1max)
    {
        return 1;
    }
    else if (z > l0min)
        return 0;
}
int toColonne(float y)
{
    if (y <= c0max && y >= c0min)
    {
        return 0;
    }
    else if (y <= c1max && y >= c1min)
    {
        return 1;
    }
    else if (y <= c2max && y >= c2min)
    {
        return 2;
    }
    else if (y <= c3max && y >= c3min)
    {
        return 3;
    }
    else if (y <= c4max && y >= c4min)
    {
        return 4;
    }
    else if (y <= c5max && y >= c5min)
    {
        return 5;
    }

}

void xtractImage(const aruco_msgs::MarkerArray& msg, vector<Piece> &pieceDep, vector<Piece> &pieceSol)
{
     // flags
    bool pp = false;  // purple 
    bool gp = false, gpF = false;  // green
    bool bp1 = false, bp1F= false, bp2 = false, bp2F = false; // blue
    bool op1 = false, op2 = false; // orange
    bool rp1 = false, rp2 = false; // red
    int ligne , colonne;

    unsigned int ppId, gpId, gpFId, bp1Id, bp1FId, bp2Id, bp2FId, op1Id, op2Id,rp1Id,rp2Id; // index in msg.markers array
    unsigned int bp1Rot=1, bp2Rot=1, gpRot=1;

    configXml("/home/najib/catkin_ws/src/camelot_jr/config.xml"); //extraction des données du fichier config xml


    
    for (int i=0; i<msg.markers.size(); i++)
    {
        int id = msg.markers[i].id;
        if ( id >= PuIDmin && id <= PuIDmax) // purple
        {
            pp = true; ppId = i;
        }
        if ( id >= GIDmin && id <= GIDmax) // green
        {
            gp = true; gpId = i;
            if(id == 1)
            {
                gpF = true;
                gpFId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2  )
                {
                    gpRot = 1;
                }
                else if( rot <= 1 && rot >= 0.8 )
                {
                    gpRot = 5;
                }
                else if( rot<=-0.9 && rot > -1  )
                {
                    gpRot = 3;
                }
            }
            else if(id == 3)
            {
                gpF = true;
                gpFId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2 )
                {
                    gpRot = 2;
                }
                else if( rot<=-0.9 && rot > -1 )
                {
                    gpRot = 4;
                }
                else if( rot <= 1 && rot >= 0.8  )
                {
                    gpRot = 6;
                }
            }
        }
        if ( id >= B1IDmin && id <= B1IDmax) // blue 1
        {
            bp1 = true; bp1Id = i;
            if(id == B1RotImpaire)
            {
                bp1F = true;
                bp1FId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2  )
                {
                    bp1Rot = 1;
                }
                else if( rot <= 1 && rot >= 0.8 )
                {
                    bp1Rot = 5;
                }
                else if( rot<=-0.9 && rot > -1  )
                {
                    bp1Rot = 3;
                }
            }
            else if(id == B2RotPaire)
            {
                bp1F = true;
                bp1FId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2 )
                {
                    bp1Rot = 2;
                }
                else if( rot<=-0.9 && rot > -1 )
                {
                    bp1Rot = 4;
                }
                else if( rot <= 1 && rot >= 0.8  )
                {
                    bp1Rot = 6;
                }
            }
        }
        if ( id >= B2IDmin && id <= B2IDmax) // blue 2 
        {
            bp2 = true; bp2Id = i;
            if(id == B2RotImpaire)
            {
                bp2F = true;
                bp2FId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2 )
                {
                    bp2Rot = 1;
                }
                else if( rot <= 1 && rot >= 0.8 )
                {
                    bp2Rot = 5;
                }
                else if(rot<=-0.9 && rot > -1 )
                {
                    bp2Rot = 3;
                }
            }
            else if(id == B2RotPaire)
            {
                bp2F = true;
                bp2FId = i;
                float rot = msg.markers[i].pose.pose.orientation.y;
                if (rot <= 0.2 && rot >= -0.2 )
                {
                    bp2Rot = 2;
                }
                else if( rot<=-0.9 && rot > -1 )
                {
                    bp2Rot = 4;
                }
                else if( rot <= 1 && rot >= 0.8  )
                {
                    bp2Rot = 6;
                }
            }
        }
        if ( id >= OP1IDmin && id <= OP1IDmax) // orange 1 
        {
            op1 = true; op1Id = i;
        }
        if ( id >= OP2IDmin && id <= OP2IDmax) // orange 2
        {
            op2 = true; op2Id = i;
        }
        if ( id >= R1IDmin && id <= R1IDmax) // red 1 
        {
            rp1 = true; rp1Id = i;
        }
        if ( id >= R2IDmin && id <= R2IDmax) // red 2
        {
            rp2 = true; rp2Id = i;
        }
    }

    if (pp)
    {
        float x = msg.markers[ppId].pose.pose.position.x;
        float y = msg.markers[ppId].pose.pose.position.y;
        if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
        {
            ligne = toLigne(msg.markers[ppId].pose.pose.position.z);
            colonne = toColonne(msg.markers[ppId].pose.pose.position.y);
            pieceDep.push_back(PurplePiece("piece violette",1,ligne,colonne));
        }
        else
        {
            pieceSol.push_back(PurplePiece("piece violette",1,0,0));
        }
        
    }
    if (gp)
    {
        if (gpF)
        {
            float x = msg.markers[gpFId].pose.pose.position.x;
            float y = msg.markers[gpFId].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[gpFId].pose.pose.position.z);
                colonne = toColonne(msg.markers[gpFId].pose.pose.position.y);
                pieceDep.push_back(BluePiece("piece verte",gpRot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(BluePiece("piece verte",1,0,0));
            }
        }
        else 
        {
            float x = msg.markers[gpId].pose.pose.position.x;
            float y = msg.markers[gpId].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[gpId].pose.pose.position.z);
                colonne = toColonne(msg.markers[gpId].pose.pose.position.y);
                pieceDep.push_back(GreenPiece("piece verte",gpRot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(GreenPiece("piece verte",1,0,0));
            }
        }
        
       
    }
    if (bp1 || bp1F)
    {
        if (bp1F)
        {
            float x = msg.markers[bp1FId].pose.pose.position.x;
            float y = msg.markers[bp1FId].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[bp1FId].pose.pose.position.z);
                colonne = toColonne(msg.markers[bp1FId].pose.pose.position.y);
                pieceDep.push_back(BluePiece("piece bleue1",bp1Rot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(BluePiece("piece bleue1",1,0,0));
            }
        }
        else
        {
            float x = msg.markers[bp1Id].pose.pose.position.x;
            float y = msg.markers[bp1Id].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[bp1Id].pose.pose.position.z);
                colonne = toColonne(msg.markers[bp1Id].pose.pose.position.y);
                pieceDep.push_back(BluePiece("piece bleue1",bp1Rot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(BluePiece("piece bleue1",1,0,0));
            }
        }
        
       
        
    }
    if (bp2 || bp2F)
    {
        if (bp2F)
        {
            float x = msg.markers[bp2FId].pose.pose.position.x;
            float y = msg.markers[bp2FId].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[bp2FId].pose.pose.position.z);
                colonne = toColonne(msg.markers[bp2FId].pose.pose.position.y);
                pieceDep.push_back(BluePiece("piece bleue2",bp2Rot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(BluePiece("piece bleue2",1,0,0));
            }
        }
        else
        {
            float x = msg.markers[bp2Id].pose.pose.position.x;
            float y = msg.markers[bp2Id].pose.pose.position.y;
            if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
            {
                ligne = toLigne(msg.markers[bp2Id].pose.pose.position.z);
                colonne = toColonne(msg.markers[bp2Id].pose.pose.position.y);
                pieceDep.push_back(BluePiece("piece bleue2",bp2Rot,ligne,colonne));
            }
            else
            {
                pieceSol.push_back(BluePiece("piece bleue2",1,0,0));
            }
        }
        
        
    }
    
    if (op1)
    {
        float x = msg.markers[op1Id].pose.pose.position.x;
        float y = msg.markers[op1Id].pose.pose.position.y;
        if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
        {
            ligne = toLigne(msg.markers[op1Id].pose.pose.position.z);
            colonne = toColonne(msg.markers[op1Id].pose.pose.position.y);
            pieceDep.push_back(OrangePiece("orange piece 1",1,ligne,colonne));
        }
        else
        {
            pieceSol.push_back(OrangePiece("orange piece 1",1,0,0));
        }
    }
    if (op2)
    {
        float x = msg.markers[op2Id].pose.pose.position.x;
        float y = msg.markers[op2Id].pose.pose.position.y;
        if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
        {
            ligne = toLigne(msg.markers[op2Id].pose.pose.position.z);
            colonne = toColonne(msg.markers[op2Id].pose.pose.position.y);
            pieceDep.push_back(OrangePiece("orange piece 2",1,ligne,colonne));
        }
        else
        {
            pieceSol.push_back(OrangePiece("orange piece 2",1,0,0));
        }
       
    }
    if (rp1)
    {
        float x = msg.markers[rp1Id].pose.pose.position.x;
        float y = msg.markers[rp1Id].pose.pose.position.y;
        if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
        {
            ligne = toLigne(msg.markers[rp1Id].pose.pose.position.z);
            colonne = toColonne(msg.markers[rp1Id].pose.pose.position.y);
            pieceDep.push_back(RedPiece("red piece 1",1,ligne+1,colonne));
        }
        else
        {
            pieceSol.push_back(RedPiece("red piece 1",1,0,0));
        }
    }
    if (rp2)
    {
        float x = msg.markers[rp2Id].pose.pose.position.x;
        float y = msg.markers[rp2Id].pose.pose.position.y;
        if (x<0 && x >-0.18 && y <0.13 && y > -0.08) // sur le socle
        {
            ligne = toLigne(msg.markers[rp2Id].pose.pose.position.z);
            colonne = toColonne(msg.markers[rp2Id].pose.pose.position.y);
            pieceDep.push_back(RedPiece("red piece 2",1,ligne+1,colonne));
        }
        else
        {
            pieceSol.push_back(RedPiece("red piece 2",1,0,0));
        }
    }

    
}

void xtractXml(const char* xmlFileName, vector<Piece> &pieceDep, vector<Piece> &pieceSol)
{
    //char* xmlFileName = "solution/solution1.xml";
    TiXmlDocument XMLdoc(xmlFileName);
    bool loadOkay = XMLdoc.LoadFile();

    if (loadOkay)
    {
        TiXmlElement *pJeu, *pPiece, *pId, *pNom, *pRotation, *pDepart, *pInGame, *pColonne, *pLigne, *pSolution;
        int id, ligne, colonne, rot, inGame, depart, solution;
        std::string nom;

        pJeu = XMLdoc.FirstChildElement( "jeu" );

        if ( pJeu )
        {
            // Parse piece
            pPiece = pJeu->FirstChildElement("piece");
            //if (pPiece) {cout << "pPiece existe" << endl;}
            while ( pPiece )
            {
                //parsing from XML
                pId = pPiece->FirstChildElement("id");
                pNom = pPiece->FirstChildElement("nom");
                pRotation = pPiece->FirstChildElement("rotation");
                pDepart =  pPiece->FirstChildElement("depart");
                pInGame =  pPiece->FirstChildElement("InGame");
                pColonne =  pPiece->FirstChildElement("colonne");
                pLigne =  pPiece->FirstChildElement("ligne");
                pSolution =  pPiece->FirstChildElement("solution");

                // extraction des donn�es
                pId->Attribute("id",&id);
                nom = pNom->Attribute("nom");
                pDepart ->Attribute("depart",&depart);
                pRotation->Attribute("rotation",&rot);
                pColonne->Attribute("colonne",&colonne);
                pLigne->Attribute("ligne",&ligne);
                pInGame->Attribute("InGame",&inGame);
                pSolution->Attribute("solution",&solution);

                cout << nom << endl;

                if (inGame)
                {
                    if (depart)
                    {
                        switch(id)
                        {
                            case 1: //chevalier
                                pieceDep.push_back(Chevalier(nom,rot,ligne,colonne));
                                break;
                            case 2: //Princesse
                                pieceDep.push_back(Princesse(nom,rot,ligne,colonne));
                                break;
                            case 3: //Blue
                                pieceDep.push_back(BluePiece(nom,rot,ligne,colonne));
                                break;
                            case 4: //Green
                                pieceDep.push_back(GreenPiece(nom,rot,ligne,colonne));
                                break;
                            case 5: //Orange
                                pieceDep.push_back(OrangePiece(nom,rot,ligne,colonne));
                                break;
                            case 6: //Purple
                                pieceDep.push_back(PurplePiece(nom,rot,ligne,colonne));
                                break;
                            case 7: //Red
                                pieceDep.push_back(RedPiece(nom,rot,ligne,colonne));
                                break;
                            default:
                                cout << "Error : La piece n'existe pas" << endl;
                        }
                        cout << "Ajout dans pieceDepart" << endl << endl;
                    }

                    if (solution)
                    {
                        switch(id)
                        {
                            case 1: //chevalier
                                pieceSol.push_back(Chevalier(nom,rot,ligne,colonne));
                                break;
                            case 2: //Princesse
                                pieceSol.push_back(Princesse(nom,rot,ligne,colonne));
                                break;
                            case 3: //Blue
                                pieceSol.push_back(BluePiece(nom,rot,ligne,colonne));
                                break;
                            case 4: //Green
                                pieceSol.push_back(GreenPiece(nom,rot,ligne,colonne));
                                break;
                            case 5: //Orange
                                pieceSol.push_back(OrangePiece(nom,rot,ligne,colonne));
                                break;
                            case 6: //Purple
                                pieceSol.push_back(PurplePiece(nom,rot,ligne,colonne));
                                break;
                            case 7: //Red
                                pieceSol.push_back(RedPiece(nom,rot,ligne,colonne));
                                break;
                            default:
                                cout << "Error : La piece n'existe pas"  << endl;
                        }
                        cout << "Ajout dans pieceSol" << endl<< endl;
                    }
                }
                pPiece = pPiece->NextSiblingElement( "piece" );
            }
        }
            cout << endl;
    }
    else
    {
        cout << "Cannot find xml file" << endl;
    }
}

void fillBoard(Board &plateau, vector<Piece> const pieceDepart)
{
    int i = 0;
    vector<Piece> tab = pieceDepart;
    while ( !tab.empty() )
    {
        int ligne = tab[i].getPosX();
        int colonne = tab[i].getPosY();
        int rot = tab[i].getRotation();
        if(ligne <=3 && colonne <=5 && rot <=6 )
        {
            plateau.ajouterPiece(tab[i]);
            tab.pop_back();
        }
        i++;
    }
}


vector<Piece> etapeResolution(vector<Piece> const pieceSol)
{
    string name;
    int i=0;
    int index = 0;
    int ligneMax = 0;
    vector<Piece> tab = pieceSol;
    vector<Piece> sortedTab;
    while ( !tab.empty() )
    {
        //recherche de l'element le plus bas
        for (int j=0;j<tab.size(); j++)
        {
            if (tab[j].getPosX() > ligneMax)
                ligneMax = tab[j].getPosX();
                index = j;
        }
        // ajout de la piece
        name = tab[index].getNom() ;
        cout << i+1 << " . Piece " << name << " (" << tab[index].getPosX() << "," << tab[index].getPosY() << ")";
        cout << " rotation : " << tab[index].getRotation() << endl;
        sortedTab.push_back(tab[index]);
        tab.erase (tab.begin() + index); //erase de index-th element of tab
        ligneMax = 0;
        i++;
    }
    
    cout << endl << endl;
    return sortedTab;
}
void resolutionXML(Board &plateau, vector<Piece> const pieceSol)
{
    int i = 0;
    int index = 0;
    int ligneMax = 0;
    string name;
    vector<Piece> tab = pieceSol;
    while ( !tab.empty() )
    {
        //recherche de l'element le plus bas
        for (int j=0;j<tab.size(); j++)
        {
            if (tab[j].getPosX() > ligneMax)
                ligneMax = tab[j].getPosX();
                index = j;
        }
        // ajout de la piece
        plateau.ajouterPiece(tab[index]);
        name = tab[index].getNom() ;
        cout << i+1 << " . Piece " << name << " (" << tab[index].getPosX() << "," << tab[index].getPosY() << ")"<< endl;
        tab.erase (tab.begin() + index); //erase de index-th element of tab
        ligneMax = 0;
        i++;
    }
    cout << endl;
}


int sensMouvement(Board &plateau)
{
    // on definie le sens d'avancement du chevalier en fonction de sa position
    // par rapport a la princesse
    int sens = plateau.getPosChevalier()[1] - plateau.getPosPrincesse()[1];
    if (sens < 0 )
    {
        return  1; // avance vers la droite
    }
    else if (sens > 0)
    {
        return -1; // avance vers la gauche
    }
    else
        return 0;
}

int monter(Board &plateau , int mouvDir)
{
    int a,b;
    int x,y;
    bool flag = false;
    bool ok = false;
    x = plateau.getPosChevalier()[0];
    y = plateau.getPosChevalier()[1];
    a = plateau.getElem(x,y + mouvDir);
    b = plateau.getElem(x-1,y + mouvDir);
    if (mouvDir == 1 )
    {
        ok = ( a == 52 || a == 53 || a == 56 || a == 57) && (b==0 || b == 52 || b == 53 || b == 56 || b == 57);
    }
    else
    {
        ok = ( a == 96 || a == 97 || a == 99 || a == 100) && (b==0 || b == 96 || b == 97 || b == 99 || b == 100);
    }



    while (ok)
    {
        flag = true;
        plateau.setElem(0,x,y);
        plateau.setElem(1,x-1,y + mouvDir);
        plateau.setPosChevalier(x-1,y + mouvDir);


        x = plateau.getPosChevalier()[0];
        y = plateau.getPosChevalier()[1];
        a = plateau.getElem(x,y + mouvDir);
        b = plateau.getElem(x-1,y + mouvDir);

        if (mouvDir == 1 )
            ok = ( a == 50 || a == 51) && (b==48 || b == 50 || b == 51);
        else
            ok = ( a == 95 || a == 96) && (b==48 || b == 95 || b == 96);
    }
   if (flag) {return 1;}
   return 0;
}

int descendre(Board &plateau, int mouvDir)
{
    int a , b , x,y;
    bool flag = false;
    bool ok = false;
    x = plateau.getPosChevalier()[0];
    y = plateau.getPosChevalier()[1];
    a = plateau.getElem(x+1,y);
    b = plateau.getElem(x+1,y + mouvDir);

    if (mouvDir == 1 )
        ok = ( a == 96 || a == 97 || a == 99 || a == 100) && (b==0 || b==2 || b==52 || b == 53 || b == 56 || b == 57);
    else
        ok = ( a == 52 || a == 53 || a == 56 || a == 57) && (b==0 || b == 2 || b==100 || b == 99 || b == 96 || b == 97);

    while (ok)
    {
        flag = true;
        if (b == 2)
        {
            plateau.setElem(0,x,y);
            plateau.setElem(12,x+1,y + mouvDir);
            plateau.setPosChevalier(x+1,y+mouvDir);
            return 1;
        }
        else if (b>50)
        {
            a = plateau.getElem(x,y+mouvDir);
            b = plateau.getElem(x,y+mouvDir+mouvDir);
            if (a == 0 && b == 0)
            {
                plateau.setElem(0,x,y);
                plateau.setElem(1,x,y + 2*mouvDir);
                plateau.setPosChevalier(x,y+2*mouvDir);
                return 1;
            }
            else return 0;
        }
        else if (b == 0)
        {
            if (x == 2)
            {
                plateau.setElem(0,x,y);
                plateau.setElem(1,x+1,y + mouvDir);
                plateau.setPosChevalier(x+1,y+mouvDir);
            }
            else
            {
                int c = plateau.getElem(x+2,y+mouvDir );

                if ( (c>2 && c<8) || c==54 || c == 55 || c ==101 || c == 102)
                {
                    plateau.setElem(0,x,y);
                    plateau.setElem(1,x+1,y + mouvDir);
                    plateau.setPosChevalier(x+1,y+mouvDir);
                    return 1;
                }
                if (mouvDir == -1)
                {
                    if (c == 52 || c == 53 || c==56 || c == 57)
                    {
                        a = plateau.getElem(x+2,y+2*mouvDir);
                        if (x ==0)
                        {
                            b = plateau.getElem(x+3,y+2*mouvDir);
                            if (b >2 && b <8)
                            {
                                if (a == 0 )
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(1,x+2,y + 2*mouvDir);
                                    plateau.setPosChevalier(x+2,y+2*mouvDir);
                                    return 1;
                                }
                                else if (a == 2)
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(12,x+2,y + 2*mouvDir);
                                    plateau.setPosChevalier(x+2,y+2*mouvDir);
                                    return 1;
                                }
                            }
                            else if (b == 56 || b ==57)
                            {
                                b = plateau.getElem(x+3,y+3*mouvDir);
                                if (b == 2)
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(12,x+3,y + 3*mouvDir);
                                    plateau.setPosChevalier(x+3,y+3*mouvDir);
                                    return 1;
                                }
                                else if( b==0)
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(1,x+3,y + 3*mouvDir);
                                    plateau.setPosChevalier(x+3,y+3*mouvDir);
                                    return 1;
                                }
                                else return 0;
                            }
                            else
                                return 0;
                        }
                         if (a == 0 )
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(1,x+2,y + 2*mouvDir);
                                    plateau.setPosChevalier(x+2,y+2*mouvDir);
                                    return 1;
                                }
                                else if (a == 2)
                                {
                                    plateau.setElem(0,x,y);
                                    plateau.setElem(12,x+2,y + 2*mouvDir);
                                    plateau.setPosChevalier(x+2,y+2*mouvDir);
                                    return 1;
                                }
                    }
                }
                else if (mouvDir == 1)
                {
                    if (c == 96 || c== 97 || c == 99 || c == 100 )
                    {
                        a = plateau.getElem(x+2,y+2*mouvDir);
                        b = plateau.getElem(x+3,y+2*mouvDir);
                        if (b >2 && b <8)
                        {
                            if (a == 0 )
                            {
                                plateau.setElem(0,x,y);
                                plateau.setElem(1,x+2,y + 2*mouvDir);
                                plateau.setPosChevalier(x+2,y+2*mouvDir);
                                return 1;
                            }
                            else if (a == 2)
                            {
                                plateau.setElem(0,x,y);
                                plateau.setElem(12,x+2,y + 2*mouvDir);
                                plateau.setPosChevalier(x+2,y+2*mouvDir);
                                return 1;
                            }
                        }

                    }
                }

                return 0;


            }
        }
        x = plateau.getPosChevalier()[0];
        y = plateau.getPosChevalier()[1];
        a = plateau.getElem(x+1,y);
        b = plateau.getElem(x+1,y + mouvDir);

        if (mouvDir == 1 )
            ok = ( a == 95 || a == 96) && (b==0);
        else
            ok = ( a == 50 || a == 51) && (b==0);

    }

    if (flag) {return 1;};
    return 0;
}

int avancer(Board &plateau)
{
    int xPosChevalier = plateau.getPosChevalier()[0];
    int yPosChevalier = plateau.getPosChevalier()[1];
    int marche =0, okMonter = 0;
    int a;
    bool ok;

    int mouvDir = sensMouvement(plateau);

    // on verifie si il ya des marches en face
    marche = plateau.getElem(xPosChevalier, yPosChevalier + mouvDir) >= 50 ;
    int enFace = plateau.getElem(xPosChevalier, yPosChevalier + mouvDir);
    int dessous = plateau.getElem(xPosChevalier + 1, yPosChevalier+mouvDir);

    if (marche)
    {
        okMonter = monter(plateau,mouvDir);
        if (okMonter)return 1;
        else
        {
            //cout << "Impossible d'avancer escalier a l'envers" << endl;
            return 0;
        }
    }
    else
    {
        if (enFace >2)  // un mur en face
        {
            //cout << "Impossible d'avancer il y a un mur en face" << endl;
            return 0;
        }
       /* else if (enFace == 2)  // princesse en face
        {
            if (dessous==0 || plateau.getElem(xPosChevalier+1,yPosChevalier) >7)
            {
                return 0;
            }
            else
            {

                plateau.setElem(0,xPosChevalier,yPosChevalier);
                plateau.setElem(12,xPosChevalier,yPosChevalier + mouvDir); // on avance dans le sens du jeu
                plateau.setPosChevalier(xPosChevalier,yPosChevalier + mouvDir);
                return 1;
            }
        }*/
        else   //rien en face
        {
            if (mouvDir == 0)
            {
                return 0;
            }
            if (mouvDir == 1 )
            {
                a = plateau.getElem(xPosChevalier + 1, yPosChevalier );
                if (a == 96 || a == 97 || a == 99 ||a == 100)
                {
                    int action = descendre(plateau,mouvDir);

                    if (action)
                        return 1;
                }
                else
                {

                    if (dessous == 0 || dessous ==  52 ||dessous ==  53 ||dessous ==  56 ||dessous ==  57 ) // le vide peut pas avancer
                    {
                        //cout << "Impossible d'avancer il n'y a pas de piece valable en face " << endl;
                        return 0;
                    }
                    else
                    {
                        if (enFace == 2)
                        {
                            plateau.setElem(0,xPosChevalier,yPosChevalier);
                            plateau.setElem(12,xPosChevalier,yPosChevalier + mouvDir); // on avance dans le sens du jeu
                            plateau.setPosChevalier(xPosChevalier,yPosChevalier + mouvDir);
                            return 1;
                        }
                        plateau.setElem(0,xPosChevalier,yPosChevalier);
                        plateau.setElem(1,xPosChevalier,yPosChevalier + mouvDir); // on avance dans le sens du jeu
                        plateau.setPosChevalier(xPosChevalier,yPosChevalier + mouvDir);
                        return 1;
                    }
                }
            }
            else
            {
                a = plateau.getElem(xPosChevalier + 1, yPosChevalier );
                if (a == 52 || a == 53 || a == 56 ||a == 57)
                {
                    int action = descendre(plateau,mouvDir);

                    if (action)
                        return 1;
                }
                else
                {

                    if (dessous == 0 || dessous ==  96 ||dessous ==  97 ||dessous ==  99 ||dessous ==  100 ) // le vide peut pas avancer
                    {
                        //cout << "Impossible d'avancer il n'y a pas de piece valable en face " << endl;
                        return 0;
                    }
                    else
                    {
                        if (enFace == 2)
                        {
                            plateau.setElem(0,xPosChevalier,yPosChevalier);
                            plateau.setElem(12,xPosChevalier,yPosChevalier + mouvDir); // on avance dans le sens du jeu
                            plateau.setPosChevalier(xPosChevalier,yPosChevalier + mouvDir);
                            return 1;
                        }
                        plateau.setElem(0,xPosChevalier,yPosChevalier);
                        plateau.setElem(1,xPosChevalier,yPosChevalier + mouvDir); // on avance dans le sens du jeu
                        plateau.setPosChevalier(xPosChevalier,yPosChevalier + mouvDir);
                        return 1;
                    }
                }
            }
        }
    }

}

int CJoinP(Board &plateau)
{
    int xC = plateau.getPosChevalier()[0];
    int yC =  plateau.getPosChevalier()[1];
    int xP = plateau.getPosPrincesse()[0];
    int yP =  plateau.getPosPrincesse()[1];

    if (xC == xP && yC == yP )
        return 1;
    return 0;

}

int testConfig(Board &plateau)
{
    bool resolu = false;
    int ok = 0;

    resolu = CJoinP(plateau);
    while(! resolu) {
        ok = avancer(plateau);
        if (!ok) return 0;
        resolu = CJoinP(plateau);

    }
    return 1;
}

//  Mr Idzim A VERFIER
//  Attention aux pointeurs qui pointent sur une zone cr�� dans une fonction
//  en sortant de la fonction la zone peut etre r� allou�e
vector<Piece>* construcPossibilites(std::vector<Piece> const pieceSol)
{
        //construction des possibilit�
    vector<Piece> tab = pieceSol;
    vector<Piece> tableauPiece[tab.size()];
    int index;
    int i = 0;
    while ( !tab.empty() )
    {
        int nbRot = 8; // maximum

        //recherche de l'element avec le moins de rotation possible
        for (int j=0;j<tab.size(); j++)
        {
            int actuRot = tab[j].getNbRotation();
            if (  actuRot <= nbRot)
            {
                nbRot = tab[j].getNbRotation();
                index = j;
            }
        }
        // creation d'un tableau de avec toutes les rotation possible de la piece

        for (int j=0; j<nbRot;j++)
        {
            tab[index].setRotation(j+1);
            tableauPiece[i].push_back(tab[index]);

        }
        tab.erase (tab.begin() + index); //erase de index-th element of tab
        i++;

    }
    return tableauPiece;
}


vector<Coordonnes> slotDispo(Board &plateau)
{
    vector<Coordonnes> tabCordonnes;
    Coordonnes cor;
    int xC = plateau.getPosChevalier()[0];
    int yC =  plateau.getPosChevalier()[1];
    int xP = plateau.getPosPrincesse()[0];
    int yP =  plateau.getPosPrincesse()[1];

    int xMin = min(xC,xP);
    int yMin = min(yC,yP);
    int yDisp = abs(yC - yP) - 1;

    for (int i = 3; i>=xMin; i--)
    {
        if (yMin >0)
        {
            for (int j=yMin+1; j<=yDisp+1; j++)
            {
                if (plateau.getElem(i,j) == 0)
                {
                    cor.x = i;
                    cor.y = j;
                    tabCordonnes.push_back(cor);
                }
            }
        }
        else
        {

            for (int j=yMin+1; j<=yDisp; j++)
            {
                if (plateau.getElem(i,j) == 0)
                {
                    cor.x = i;
                    cor.y = j;
                    tabCordonnes.push_back(cor);
                }
            }
        }
    }
    return tabCordonnes;
}


int posable(Piece &p, Board &plateau, Coordonnes cor)
{
    int id = p.getId();
    int x = cor.x;
    int y = cor.y;
    int rot, a;

    if (plateau.getElem(x,y) == 0) // si l'espace est vide
    {
        if (id == 6 ) // piece violet 1 seule rotation
        {
            if (x == 3)
            {
                return 1;
            }
            else
            {
                a = plateau.getElem(x+1,y) ;
                if ( a == 0 || a == 96 || a == 97 || a == 52 || a == 53 || a == 99 || a == 100 || a == 56 || a == 57 )
                {
                    return 0;
                }
                else
                    return 1;
            }
        }

        else if (id == 3) // piece bleu
        {
             rot = p.getRotation();

             if (rot == 1 || rot == 2)
             {
                 if (x == 0) // bord du canvas on peut rien mettre au dessus
                 {
                     return 0;
                 }
                 if ( plateau.getElem(x-1,y) == 0)
                 {
                     if ( x == 3)
                     {
                         return 1;
                     }
                     else
                     {
                        a = plateau.getElem(x+1,y) ;
                        if ( a >2 && a <10 )
                        {
                            return 1;
                        }
                        else
                            return 0;
                     }
                 }
                 else
                    return 0;

             }
             else if (rot == 3 || rot == 4)
             {
                 if ( plateau.getElem(x,y+1) == 0 && y <5) // y=5 bord a droite
                 {
                     if ( x == 3)
                     {
                         return 1;
                     }
                     else
                     {
                        a = plateau.getElem(x+1,y) ;
                        if ( a == 0 || a == 96 || a == 97 || a == 52 || a == 53 || a == 99 || a == 100 || a == 56 || a == 57 )
                        {
                            return 0;
                        }
                        else
                            return 1;
                     }
                 }
                 else
                    return 0;
             }
             else if (rot == 5 || rot == 6)
             {
                 if ( plateau.getElem(x,y-1) == 0 && y >0 ) // emplacament a gauche est vide, y>0 bord a gauche
                 {
                     if (x == 3)
                     {
                         return 1;
                     }
                     else
                     {
                        a = plateau.getElem(x+1,y) ;
                        if ( a == 0 || a == 96 || a == 97 || a == 52 || a == 53 || a == 99 || a == 100 || a == 56 || a == 57 )
                        {
                            return 0;
                        }
                        else
                            return 1;
                     }
                 }
                 else
                    return 0;

             }
        }

        else if (id == 4) // piece verte
        {
             rot = p.getRotation();

             if (rot == 1 || rot == 2)
             {
                 if (x < 2)  // depasse le bord en haut
                 {
                     return 0;
                 }
                 else
                 {
                     if (plateau.getElem(x-1,y) == 0 && plateau.getElem(x-2,y) == 0) // emplacement vide
                     {
                         if (x == 3)  // base du Board
                         {
                             return 1;
                         }
                         else
                         {
                            a = plateau.getElem(x+1,y) ;
                            if ( a == 0 || a >50 )
                            {
                                return 0;
                            }
                            else
                                return 1;

                         }
                     }

                    else
                        return 0;
                 }

             }
             else if (rot == 3 )
             {
                 if (y > 3)  // deppase les bords
                 {
                     return 0;
                 }
                 else
                 {
                     if (plateau.getElem(x,y+1) == 0 && plateau.getElem(x,y+2) == 0) // emplacement vide
                     {
                         if (x == 3)  // base du Board
                         {
                             return 1;
                         }
                         else
                         {
                            a = plateau.getElem(x+1,y+1) ;
                            if ( a == 0 || a >50 )
                            {
                                a = plateau.getElem(x,y);
                                int b = plateau.getElem(x,y+2);
                                if  (a == 0 || a>50 || b == 0 || b > 50)
                                {
                                    return 0;
                                }
                                else
                                    return 1;
                            }
                            else
                                return 1;

                         }
                     }
                     else
                        return 0;

                 }
             }
             else if (rot == 4)
             {
                 if (y > 3)  // deppase les bords
                 {
                     return 0;
                 }
                 else
                 {
                     if (plateau.getElem(x,y+1) == 0 && plateau.getElem(x,y+2) == 0) // emplacement vide
                     {
                         if (x == 3)  // base du Board
                         {
                             return 1;
                         }
                         else
                         {
                            a = plateau.getElem(x+1,y+1) ;
                            if ( a == 0 || a >50 )
                            {
                                a = plateau.getElem(x+1,y);
                                int b = plateau.getElem(x+1,y+2);
                                if  (a==0 || a==99 || a==100 || a==56 || a==57 || b==0 || b==99 || b==100 || b==56 || b==57)
                                {
                                    return 0;
                                }
                                else
                                    return 1;
                            }
                            else
                                return 1;

                         }
                     }
                     else
                        return 0;

                 }
             }
             else if (rot == 5)
             {
                 if (y < 2)  // deppase les bords
                 {
                     return 0;
                 }
                 else
                 {
                     if (plateau.getElem(x,y-1) == 0 && plateau.getElem(x,y-2) == 0) // emplacement vide
                     {
                         if (x == 3)  // base du Board
                         {
                             return 1;
                         }
                         else
                         {
                            a = plateau.getElem(x+1,y-1) ;
                            if ( a == 0 || a >50 )
                            {
                                a = plateau.getElem(x+1,y);
                                int b = plateau.getElem(x+1,y-2);
                                if  (a==0 || a==99 || a==100 || a==56 || a==57 || b==0 || b==99 || b==100 || b==56 || b==57)
                                {
                                    return 0;
                                }
                                else
                                    return 1;
                            }
                            else
                                return 1;

                         }
                     }
                     else
                        return 0;

                 }
             }
             else if (rot == 6)
             {
                 if (y < 2)  // deppase les bords
                 {
                     return 0;
                 }
                 else
                 {
                     if (plateau.getElem(x,y-1) == 0 && plateau.getElem(x,y-2) == 0) // emplacement vide
                     {
                         if (x == 3)  // base du Board
                         {
                             return 1;
                         }
                         else
                         {
                            a = plateau.getElem(x+1,y-1) ;
                            if ( a == 0 || a >50 )
                            {
                                a = plateau.getElem(x,y);
                                int b = plateau.getElem(x,y-2);
                                if  (a == 0 || a>50 || b == 0 || b > 50)
                                {
                                    return 0;
                                }
                                else
                                    return 1;
                            }
                            else
                                return 1;

                         }
                     }
                     else
                        return 0;

                 }

             }
        }

    }
}




vector<Piece> resolution(Board &plateau, std::vector<Piece> const pieceSol)
{
    //construction des possibilit�
    vector<Piece> tab = pieceSol;
    vector<Piece> tableauPiece[tab.size()];
    int tableauPieceSize = tab.size();
    int index;
    int i = 0;
    while ( !tab.empty() )
    {
        int nbRot = 6; // maximum

        //recherche de l'element avec le moins de rotation possible
        for (int j=0;j<tab.size(); j++)
        {
            int actuRot = tab[j].getNbRotation();
            if (  actuRot <= nbRot)
            {
                nbRot = tab[j].getNbRotation();
                index = j;
            }
        }
        // creation d'un tableau avec toutes les rotation possible de la piece

        for (int j=0; j<nbRot;j++)
        {
            tab[index].setRotation(j+1);
            tableauPiece[i].push_back(tab[index]);

        }
        tab.erase (tab.begin() + index); //erase de index-th element of tab
        i++;

    }

    /** slot disponible **/

    vector<Coordonnes> espaceVide =  slotDispo(plateau);
 

    /*** RESOLUTION ***/



    int curseur ;
    Piece piece1, piece2, piece3,piece4;
    Coordonnes cor1,cor2,cor3,cor4;
    int ok,resolu=0;
    int iteration = 0;


    // construction des combinaison possible
    vector<PieceCorr> combine1;
    vector<Cas2Piece> combine2;
    vector<Cas3Piece> combine3;
    vector<Cas4Piece> combine4;

    if (tableauPieceSize == 1)
    {
        cout << "nb espace vide = " << espaceVide.size() << endl; 
        PieceCorr a;
        if(tableauPiece[0][0].getId() == 6) // piece violet
        {
            a.p = tableauPiece[0][0];
            for (int i = 0; i<espaceVide.size(); i++)
            {
                a.cor = espaceVide[i];
                combine1.push_back(a);
            }
        }
        else
        {
            for (int i=0; i<6; i++)
            {
                a.p = tableauPiece[0][i];
                for (int j = 0; j<espaceVide.size(); j++)
                {
                    a.cor = espaceVide[j];
                    combine1.push_back(a);
                   
                }
            }
        }
    }

    else if (tableauPieceSize == 2)
    {
        Cas2Piece poss;
        PieceCorr a,b;

        if (tableauPiece[0][0].getId() == 6 ) // piece violet
        {
            for (int i = 0; i<tableauPieceSize; i++) // de 0 a 1
            {
                for (int j = 0; j<tableauPiece[1].size(); j++)
                {
                    a.p = tableauPiece[0][0];
                    b.p = tableauPiece[1][j];
                    for (int k = 0; k<espaceVide.size(); k++)
                    {
                        a.cor = espaceVide[k];
                        for (int v = 0; v<espaceVide.size(); v++)
                        {
                            b.cor = espaceVide[v];
                            poss.p1 = a;
                            poss.p2 = b;
                            combine2.push_back(poss);
                        }
                    }

                }
            }
        }
        else
        {
            for (int i = 0; i<6; i++)
            {
                for (int j = 0; j<6; j++)
                {
                    a.p = tableauPiece[0][i];
                    b.p = tableauPiece[1][j];
                    for (int k = 0; k<espaceVide.size(); k++)
                    {
                        a.cor = espaceVide[k];
                        for (int v = 0; v<espaceVide.size(); v++)
                        {
                            b.cor = espaceVide[v];
                            poss.p1 = a;
                            poss.p2 = b;
                            combine2.push_back(poss);
                        }
                    }

                }
            }
        }

    }

    else if (tableauPieceSize == 3)
    {
        Cas3Piece poss;
        PieceCorr a,b,c;

        if (tableauPiece[0][0].getId() == 6 ) // piece violet
        {
            for (int i = 0; i<tableauPieceSize; i++) //de 0 a 2
            {
                for (int j = 0; j<tableauPiece[1].size(); j++)
                {
                    for (int l = 0; l<tableauPiece[2].size();l++)
                    {
                        a.p = tableauPiece[0][0];
                        b.p = tableauPiece[1][j];
                        c.p = tableauPiece[2][l];
                        for (int k = 0; k<espaceVide.size(); k++)
                        {
                            a.cor = espaceVide[k];
                            for (int v = 0; v<espaceVide.size(); v++)
                            {
                                b.cor = espaceVide[v];
                                for (int s=0; s<espaceVide.size(); s++)
                                {
                                    c.cor = espaceVide[s];

                                    poss.p1 = a;
                                    poss.p2 = b;
                                    poss.p3 = c;
                                    combine3.push_back(poss);
                                }

                            }
                        }
                    }

                }
            }
        }
        else
        {
            for (int i = 0; i<6; i++) //de 0 a 2
            {
                for (int j = 0; j<6; j++)
                {
                    for (int l = 0; l<6;l++)
                    {


                        a.p = tableauPiece[0][i];
                        b.p = tableauPiece[1][j];
                        c.p = tableauPiece[2][l];
                        for (int k = 0; k<espaceVide.size(); k++)
                        {
                            a.cor = espaceVide[k];
                            for (int v = 0; v<espaceVide.size(); v++)
                            {
                                b.cor = espaceVide[v];
                                for (int s=0; s<espaceVide.size(); s++)
                                {
                                    c.cor = espaceVide[s];

                                    poss.p1 = a;
                                    poss.p2 = b;
                                    poss.p3 = c;
                                    combine3.push_back(poss);
                                }

                            }
                        }
                    }

                }
            }
        }

    }

    else if (tableauPieceSize == 4)
    {
        int err = 0;
        Cas4Piece poss;
        PieceCorr a,b,c,d;

        if (tableauPiece[0][0].getId() == 6 ) // piece violet
        {
            for (int i = 0; i<1; i++) //de 0 a 3
            {
                for (int j = 0; j<6; j++)
                {
                    for (int k = 0; k<6;k++)
                    {
                        for (int l=0;l<6;l++)
                        {
                            a.p = tableauPiece[0][0];
                            b.p = tableauPiece[1][j];
                            c.p = tableauPiece[2][k];
                            d.p = tableauPiece[3][l];
                            for (int m = 0; m<espaceVide.size(); m++)
                            {
                                a.cor = espaceVide[m];
                                for (int n = 0; n<espaceVide.size(); n++)
                                {
                                    b.cor = espaceVide[n];
                                    for (int o=0; o<espaceVide.size(); o++)
                                    {
                                        c.cor = espaceVide[o];
                                        for (int p=0;p<espaceVide.size();p++)
                                        {
                                            d.cor = espaceVide[p];


                                                poss.p1 = a;
                                                poss.p2 = b;
                                                poss.p3 = c;
                                                poss.p4 = d;

                                                int ok1,ok2,ok3,ok4;
                                                curseur = combine4.size();

                                                    Board boardTest = plateau; // reprendre le plateau de depart a chaque iteration

                                                    piece1 = poss.p1.p;
                                                    cor1 = poss.p1.cor;
                                                    piece2 = poss.p2.p;
                                                    cor2 = poss.p2.cor;
                                                    piece3 = poss.p3.p;
                                                    cor3 = poss.p3.cor;
                                                    piece4 = poss.p4.p;
                                                    cor4 = poss.p4.cor;
                                               
                                                   ok1 =  posable(piece1,boardTest,cor1);
                                                   ok2 =  posable(piece2,boardTest,cor2);
                                                   ok3 =  posable(piece3,boardTest,cor3);
                                                   ok4 =  posable(piece4,boardTest,cor4);
                                                   if (ok1) // piece 1 posable
                                                   {

                                                       piece1.setPosX(cor1.x);
                                                       piece1.setPosY(cor1.y);
                                                       boardTest.ajouterPiece(piece1);
                                                       ok2 = posable(piece2,boardTest,cor2);
                                                       ok3 = posable(piece3,boardTest,cor3);
                                                       ok4 = posable(piece4,boardTest,cor4);
                                                       if (ok2) // piece 2 posable
                                                       {

                                                           piece2.setPosX(cor2.x);
                                                           piece2.setPosY(cor2.y);
                                                           boardTest.ajouterPiece(piece2);
                                                           ok3 = posable(piece3,boardTest,cor3);
                                                           ok4 = posable(piece4,boardTest,cor4);
                                                           if (ok3)
                                                           {
                                                               piece3.setPosX(cor3.x);
                                                               piece3.setPosY(cor3.y);
                                                               boardTest.ajouterPiece(piece3);
                                                               ok4 = posable(piece4,boardTest,cor4);
                                                               if (ok4)
                                                               {
                                                                   piece4.setPosX(cor4.x);
                                                                   piece4.setPosY(cor4.y);
                                                                   boardTest.ajouterPiece(piece4);
                                                                   resolu = testConfig(boardTest);
                                                               }

                                                           }
                                                           else if (ok4)
                                                           {
                                                               piece4.setPosX(cor4.x);
                                                               piece4.setPosY(cor4.y);
                                                               boardTest.ajouterPiece(piece4);
                                                               ok3 = posable(piece3,boardTest,cor3);
                                                               if (ok3)
                                                               {
                                                                   piece3.setPosX(cor3.x);
                                                                   piece3.setPosY(cor3.y);
                                                                   boardTest.ajouterPiece(piece3);
                                                                   resolu = testConfig(boardTest);
                                                               }
                                                           }


                                                       }
                                                       else if (ok3)
                                                       {
                                                           piece3.setPosX(cor3.x);
                                                           piece3.setPosY(cor3.y);
                                                           boardTest.ajouterPiece(piece3);
                                                           ok2 = posable(piece2,boardTest,cor2);
                                                           ok4 = posable(piece4,boardTest,cor4);
                                                           if (ok2)
                                                           {
                                                               piece2.setPosX(cor2.x);
                                                               piece2.setPosY(cor2.y);
                                                               boardTest.ajouterPiece(piece2);
                                                               ok4 = posable(piece4,boardTest,cor4);
                                                               if (ok4)
                                                               {
                                                                    piece4.setPosX(cor4.x);
                                                                    piece4.setPosY(cor4.y);
                                                                    boardTest.ajouterPiece(piece4);
                                                                    resolu = testConfig(boardTest);
                                                               }

                                                           }
                                                           else if (ok4)
                                                           {
                                                                piece4.setPosX(cor4.x);
                                                                piece4.setPosY(cor4.y);
                                                                boardTest.ajouterPiece(piece4);
                                                                ok2 = posable(piece2,boardTest,cor2);
                                                                if(ok2)
                                                                {
                                                                    piece2.setPosX(cor2.x);
                                                                    piece2.setPosY(cor2.y);
                                                                    boardTest.ajouterPiece(piece2);
                                                                    resolu = testConfig(boardTest);
                                                                }
                                                           }

                                                       }
                                                       else if (ok4)
                                                       {
                                                            piece4.setPosX(cor4.x);
                                                            piece4.setPosY(cor4.y);
                                                            boardTest.ajouterPiece(piece4);
                                                            ok2 = posable(piece2,boardTest,cor2);
                                                            ok3 = posable(piece3,boardTest,cor3);
                                                            if (ok2)
                                                            {
                                                                piece2.setPosX(cor2.x);
                                                                piece2.setPosY(cor2.y);
                                                                boardTest.ajouterPiece(piece2);
                                                                ok3 = posable(piece3,boardTest,cor3);
                                                                if (ok3)
                                                                {
                                                                    piece3.setPosX(cor3.x);
                                                                    piece3.setPosY(cor3.y);
                                                                    boardTest.ajouterPiece(piece3);
                                                                    resolu = testConfig(boardTest);
                                                                }
                                                            }
                                                            else if (ok3)
                                                            {
                                                                piece3.setPosX(cor3.x);
                                                                piece3.setPosY(cor3.y);
                                                                boardTest.ajouterPiece(piece3);
                                                                ok2 = posable(piece2,boardTest,cor2);
                                                                if (ok2)
                                                                {
                                                                    piece2.setPosX(cor2.x);
                                                                    piece2.setPosY(cor2.y);
                                                                    boardTest.ajouterPiece(piece2);
                                                                    resolu = testConfig(boardTest);
                                                                }
                                                            }
                                                       }
                                                   }

                                                   else if (ok2) // piece1 pas posable on test avec la piece 2
                                                   {
                                                       piece2.setPosX(cor2.x);
                                                       piece2.setPosY(cor2.y);
                                                       boardTest.ajouterPiece(piece2);
                                                       ok1 = posable(piece1,boardTest,cor1);
                                                       ok3 =  posable(piece3,boardTest,cor3);
                                                       if (ok1) // piece 1 posable
                                                       {

                                                           piece1.setPosX(cor1.x);
                                                           piece1.setPosY(cor1.y);
                                                           boardTest.ajouterPiece(piece1);
                                                           ok3 = posable(piece3,boardTest,cor3);
                                                           if (ok3) // piece 3 posable
                                                           {

                                                               piece3.setPosX(cor3.x);
                                                               piece3.setPosY(cor3.y);
                                                               boardTest.ajouterPiece(piece3);
                                                               

                                                               resolu = testConfig(boardTest);

                                                           }
                                                       }
                                                       else if (ok3)
                                                       {
                                                           piece3.setPosX(cor3.x);
                                                           piece3.setPosY(cor3.y);
                                                           boardTest.ajouterPiece(piece3);
                                                           ok1 = posable(piece1,boardTest,cor1);
                                                           if (ok1)
                                                           {
                                                               piece1.setPosX(cor1.x);
                                                               piece1.setPosY(cor1.y);
                                                               boardTest.ajouterPiece(piece1);                                                            
                                                               resolu = testConfig(boardTest);

                                                           }

                                                       }

                                                   }

                                                   else if (ok3) // piece1 et piece 2 pas posable on test avec la piece 2
                                                   {
                                                       piece3.setPosX(cor3.x);
                                                       piece3.setPosY(cor3.y);
                                                       boardTest.ajouterPiece(piece3);
                                                       ok1 = posable(piece1,boardTest,cor1);
                                                       ok2 =  posable(piece2,boardTest,cor2);
                                                       if (ok1) // piece 1 posable
                                                       {

                                                           piece1.setPosX(cor1.x);
                                                           piece1.setPosY(cor1.y);
                                                           boardTest.ajouterPiece(piece1);
                                                           ok2 = posable(piece2,boardTest,cor2);
                                                           if (ok2) // piece 3 posable
                                                           {

                                                               piece2.setPosX(cor2.x);
                                                               piece2.setPosY(cor2.y);
                                                               boardTest.ajouterPiece(piece2);                                                               
                                                               resolu = testConfig(boardTest);

                                                           }
                                                       }
                                                       else if (ok2)
                                                       {
                                                           piece2.setPosX(cor2.x);
                                                           piece2.setPosY(cor2.y);
                                                           boardTest.ajouterPiece(piece2);
                                                           ok1 = posable(piece1,boardTest,cor1);
                                                           if (ok1)
                                                           {
                                                               piece1.setPosX(cor1.x);
                                                               piece1.setPosY(cor1.y);
                                                               boardTest.ajouterPiece(piece1);
                                                               resolu = testConfig(boardTest);

                                                           }

                                                       }

                                                   }

                                                   if (resolu)
                                                   {
                                                       cout << "ok j'ai trouve" << endl;
                                                       vector<Piece> solArray;
                                                       solArray.push_back(piece1);
                                                       solArray.push_back(piece2);
                                                       solArray.push_back(piece3);
                                                       solArray.push_back(piece4);
                                                       boardTest.print();
                                                       return solArray;
                                                   }


                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }

                }
            }
        }




   

    if (tableauPieceSize == 1)
    {
        cout << "Dans le cas resolution 1 piece" << endl;
        curseur = combine1.size();
        while (! resolu && !combine1.empty())
        {
            Board boardTest = plateau;
            piece1 = combine1[curseur - 1].p;
            cor1 = combine1[curseur - 1].cor;
            ok = posable(piece1,boardTest,cor1);

            if(ok) // piece posable
            {
                
                piece1.setPosX(cor1.x);
                piece1.setPosY(cor1.y);
                boardTest.ajouterPiece(piece1);
                resolu = testConfig(boardTest);
            }
            if (resolu)
            {
                vector<Piece> solArray;
                solArray.push_back(piece1);
                cout << "ok j'ai trouve" << endl;
                boardTest.print();
                return solArray;
            }
            combine1.pop_back();
            curseur = combine1.size();
        }

    }
    if (tableauPieceSize == 2)
    {
        curseur = combine2.size();
        while (!resolu && !combine2.empty() )
        {
            Board boardTest = plateau; // reprendre le plateau de depart a chaque iteration

            piece1 = combine2[curseur-1].p1.p;
            cor1 = combine2[curseur-1].p1.cor;
            piece2 = combine2[curseur-1].p2.p;
            cor2 = combine2[curseur-1].p2.cor;
            ok =  posable(piece1,boardTest,cor1);

           if (ok) // piece 1 posable
           {

               piece1.setPosX(cor1.x);
               piece1.setPosY(cor1.y);
               boardTest.ajouterPiece(piece1);
               ok = posable(piece2,boardTest,cor2);
               if (ok) // piece 2 posable
               {

                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   resolu = testConfig(boardTest);

               }
           }
           else // piece1 pas posable on test avec la piece 2
           {
               ok = posable(piece2,boardTest,cor2);
               if (ok) // piece 2 posable
               {

                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   ok = posable(piece1,boardTest,cor1);
                   if (ok) // piece 1 posable
                   {

                       piece1.setPosX(cor1.x);
                       piece1.setPosY(cor1.y);
                       boardTest.ajouterPiece(piece1);
                       resolu = testConfig(boardTest);

                   }
               }

           }
           if (resolu)
           {
               vector<Piece> solArray;
               solArray.push_back(piece1);
               solArray.push_back(piece2);
               cout << "ok j'ai trouve" << endl;
               boardTest.print();
               return solArray;
           }
          //combine.erase (combine.begin() + curseur); //erase de index-th element of tab
          combine2.pop_back();
          curseur = combine2.size();
        }
    }

    else if (tableauPieceSize == 3)
    {
        int ok1,ok2,ok3;
        curseur = combine3.size();
        while (!resolu && !combine3.empty() )
        {
            Board boardTest = plateau; // reprendre le plateau de depart a chaque iteration

            piece1 = combine3[curseur-1].p1.p;
            cor1 = combine3[curseur-1].p1.cor;
            piece2 = combine3[curseur-1].p2.p;
            cor2 = combine3[curseur-1].p2.cor;
            piece3 = combine3[curseur-1].p3.p;
            cor3 = combine3[curseur-1].p3.cor;

           ok1 =  posable(piece1,boardTest,cor1);
           ok2 =  posable(piece2,boardTest,cor2);
           ok3 =  posable(piece3,boardTest,cor3);

           if (ok1) // piece 1 posable
           {

               piece1.setPosX(cor1.x);
               piece1.setPosY(cor1.y);
               boardTest.ajouterPiece(piece1);
               ok2 = posable(piece2,boardTest,cor2);
               ok3 = posable(piece3,boardTest,cor3);
               if (ok2) // piece 2 posable
               {

                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   ok3 = posable(piece3,boardTest,cor3);
                   if (ok3)
                   {
                       piece3.setPosX(cor3.x);
                       piece3.setPosY(cor3.y);
                       boardTest.ajouterPiece(piece3);
                       resolu = testConfig(boardTest);
                   }


               }
               else if (ok3)
               {
                   piece3.setPosX(cor3.x);
                   piece3.setPosY(cor3.y);
                   boardTest.ajouterPiece(piece3);
                   ok2 = posable(piece2,boardTest,cor2);
                   if (ok2)
                   {
                       piece2.setPosX(cor2.x);
                       piece2.setPosY(cor2.y);
                       boardTest.ajouterPiece(piece2);
                       resolu = testConfig(boardTest);
                   }

               }
           }

           else if (ok2) // piece1 pas posable on test avec la piece 2
           {
               piece2.setPosX(cor2.x);
               piece2.setPosY(cor2.y);
               boardTest.ajouterPiece(piece2);
               ok1 = posable(piece1,boardTest,cor1);
               ok3 =  posable(piece3,boardTest,cor3);
               if (ok1) // piece 1 posable
               {

                   piece1.setPosX(cor1.x);
                   piece1.setPosY(cor1.y);
                   boardTest.ajouterPiece(piece1);
                   ok3 = posable(piece3,boardTest,cor3);
                   if (ok3) // piece 3 posable
                   {

                       piece3.setPosX(cor3.x);
                       piece3.setPosY(cor3.y);
                       boardTest.ajouterPiece(piece3);
                       resolu = testConfig(boardTest);

                   }
               }
               else if (ok3)
               {
                   piece3.setPosX(cor3.x);
                   piece3.setPosY(cor3.y);
                   boardTest.ajouterPiece(piece3);
                   ok1 = posable(piece1,boardTest,cor1);
                   if (ok1)
                   {
                       piece1.setPosX(cor1.x);
                       piece1.setPosY(cor1.y);
                       boardTest.ajouterPiece(piece1);
                       resolu = testConfig(boardTest);

                   }

               }

           }

           else if (ok3) // piece1 et piece 2 pas posable on test avec la piece 2
           {
               piece3.setPosX(cor3.x);
               piece3.setPosY(cor3.y);
               boardTest.ajouterPiece(piece3);
               ok1 = posable(piece1,boardTest,cor1);
               ok2 =  posable(piece2,boardTest,cor2);
               if (ok1) // piece 1 posable
               {

                   piece1.setPosX(cor1.x);
                   piece1.setPosY(cor1.y);
                   boardTest.ajouterPiece(piece1);
                   ok2 = posable(piece2,boardTest,cor2);
                   if (ok2) // piece 3 posable
                   {

                       piece2.setPosX(cor2.x);
                       piece2.setPosY(cor2.y);
                       boardTest.ajouterPiece(piece2);
                       resolu = testConfig(boardTest);

                   }
               }
               else if (ok2)
               {
                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   ok1 = posable(piece1,boardTest,cor1);
                   if (ok1)
                   {
                       piece1.setPosX(cor1.x);
                       piece1.setPosY(cor1.y);
                       boardTest.ajouterPiece(piece1);
                       resolu = testConfig(boardTest);

                   }

               }

           }

           if (resolu)
           {
               cout << "ok j'ai trouve" << endl;
               boardTest.print();
               vector<Piece> solArray;
               solArray.push_back(piece1);
               solArray.push_back(piece2);
               solArray.push_back(piece3);
              
               return solArray;
           }
          combine3.pop_back();
          curseur = combine3.size();
        }
    }

    else if (tableauPieceSize == 4)
    {
        int ok1,ok2,ok3,ok4;
        curseur = combine4.size();
        while (!resolu && !combine4.empty() )
        {
            Board boardTest = plateau; // reprendre le plateau de depart a chaque iteration

            piece1 = combine4[curseur-1].p1.p;
            cor1 = combine4[curseur-1].p1.cor;
            piece2 = combine4[curseur-1].p2.p;
            cor2 = combine4[curseur-1].p2.cor;
            piece3 = combine4[curseur-1].p3.p;
            cor3 = combine4[curseur-1].p3.cor;
            piece4 = combine4[curseur-1].p4.p;
            cor4 = combine4[curseur-1].p4.cor;

           ok1 =  posable(piece1,boardTest,cor1);
           ok2 =  posable(piece2,boardTest,cor2);
           ok3 =  posable(piece3,boardTest,cor3);
           ok4 =  posable(piece4,boardTest,cor4);
           if (ok1) // piece 1 posable
           {

               piece1.setPosX(cor1.x);
               piece1.setPosY(cor1.y);
               boardTest.ajouterPiece(piece1);
               ok2 = posable(piece2,boardTest,cor2);
               ok3 = posable(piece3,boardTest,cor3);
               ok4 = posable(piece4,boardTest,cor4);
               if (ok2) // piece 2 posable
               {

                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   ok3 = posable(piece3,boardTest,cor3);
                   ok4 = posable(piece4,boardTest,cor4);
                   if (ok3)
                   {
                       piece3.setPosX(cor3.x);
                       piece3.setPosY(cor3.y);
                       boardTest.ajouterPiece(piece3);
                       ok4 = posable(piece4,boardTest,cor4);
                       if (ok4)
                       {
                           piece4.setPosX(cor4.x);
                           piece4.setPosY(cor4.y);
                           boardTest.ajouterPiece(piece4);
                           resolu = testConfig(boardTest);
                       }

                   }
                   else if (ok4)
                   {
                       piece4.setPosX(cor4.x);
                       piece4.setPosY(cor4.y);
                       boardTest.ajouterPiece(piece4);
                       ok3 = posable(piece3,boardTest,cor3);
                       if (ok3)
                       {
                           piece3.setPosX(cor3.x);
                           piece3.setPosY(cor3.y);
                           boardTest.ajouterPiece(piece3);
                           resolu = testConfig(boardTest);
                       }
                   }


               }
               else if (ok3)
               {
                   piece3.setPosX(cor3.x);
                   piece3.setPosY(cor3.y);
                   boardTest.ajouterPiece(piece3);
                   ok2 = posable(piece2,boardTest,cor2);
                   ok4 = posable(piece4,boardTest,cor4);
                   if (ok2)
                   {
                       piece2.setPosX(cor2.x);
                       piece2.setPosY(cor2.y);
                       boardTest.ajouterPiece(piece2);
                       ok4 = posable(piece4,boardTest,cor4);
                       if (ok4)
                       {
                            piece4.setPosX(cor4.x);
                            piece4.setPosY(cor4.y);
                            boardTest.ajouterPiece(piece4);
                            resolu = testConfig(boardTest);
                       }

                   }
                   else if (ok4)
                   {
                        piece4.setPosX(cor4.x);
                        piece4.setPosY(cor4.y);
                        boardTest.ajouterPiece(piece4);
                        ok2 = posable(piece2,boardTest,cor2);
                        if(ok2)
                        {
                            piece2.setPosX(cor2.x);
                            piece2.setPosY(cor2.y);
                            boardTest.ajouterPiece(piece2);
                            resolu = testConfig(boardTest);
                        }
                   }

               }
               else if (ok4)
               {
                    piece4.setPosX(cor4.x);
                    piece4.setPosY(cor4.y);
                    boardTest.ajouterPiece(piece4);
                    ok2 = posable(piece2,boardTest,cor2);
                    ok3 = posable(piece3,boardTest,cor3);
                    if (ok2)
                    {
                        piece2.setPosX(cor2.x);
                        piece2.setPosY(cor2.y);
                        boardTest.ajouterPiece(piece2);
                        ok3 = posable(piece3,boardTest,cor3);
                        if (ok3)
                        {
                            piece3.setPosX(cor3.x);
                            piece3.setPosY(cor3.y);
                            boardTest.ajouterPiece(piece3);
                            resolu = testConfig(boardTest);
                        }
                    }
                    else if (ok3)
                    {
                        piece3.setPosX(cor3.x);
                        piece3.setPosY(cor3.y);
                        boardTest.ajouterPiece(piece3);
                        ok2 = posable(piece2,boardTest,cor2);
                        if (ok2)
                        {
                            piece2.setPosX(cor2.x);
                            piece2.setPosY(cor2.y);
                            boardTest.ajouterPiece(piece2);
                            resolu = testConfig(boardTest);
                        }
                    }
               }
           }

           else if (ok2) // piece1 pas posable on test avec la piece 2
           {
               piece2.setPosX(cor2.x);
               piece2.setPosY(cor2.y);
               boardTest.ajouterPiece(piece2);
               ok1 = posable(piece1,boardTest,cor1);
               ok3 =  posable(piece3,boardTest,cor3);
               if (ok1) // piece 1 posable
               {

                   piece1.setPosX(cor1.x);
                   piece1.setPosY(cor1.y);
                   boardTest.ajouterPiece(piece1);
                   ok3 = posable(piece3,boardTest,cor3);
                   if (ok3) // piece 3 posable
                   {

                       piece3.setPosX(cor3.x);
                       piece3.setPosY(cor3.y);
                       boardTest.ajouterPiece(piece3);
                       //boardTest.print();
                       //boardTest.printDebug();

                       resolu = testConfig(boardTest);

                   }
               }
               else if (ok3)
               {
                   piece3.setPosX(cor3.x);
                   piece3.setPosY(cor3.y);
                   boardTest.ajouterPiece(piece3);
                   ok1 = posable(piece1,boardTest,cor1);
                   if (ok1)
                   {
                       piece1.setPosX(cor1.x);
                       piece1.setPosY(cor1.y);
                       boardTest.ajouterPiece(piece1);
                       //boardTest.print();
                       resolu = testConfig(boardTest);

                   }

               }

           }

           else if (ok3) // piece1 et piece 2 pas posable on test avec la piece 2
           {
               piece3.setPosX(cor3.x);
               piece3.setPosY(cor3.y);
               boardTest.ajouterPiece(piece3);
               ok1 = posable(piece1,boardTest,cor1);
               ok2 =  posable(piece2,boardTest,cor2);
               if (ok1) // piece 1 posable
               {

                   piece1.setPosX(cor1.x);
                   piece1.setPosY(cor1.y);
                   boardTest.ajouterPiece(piece1);
                   ok2 = posable(piece2,boardTest,cor2);
                   if (ok2) // piece 3 posable
                   {

                       piece2.setPosX(cor2.x);
                       piece2.setPosY(cor2.y);
                       boardTest.ajouterPiece(piece2);
                       //boardTest.print();
                       //boardTest.printDebug();

                       resolu = testConfig(boardTest);

                   }
               }
               else if (ok2)
               {
                   piece2.setPosX(cor2.x);
                   piece2.setPosY(cor2.y);
                   boardTest.ajouterPiece(piece2);
                   ok1 = posable(piece1,boardTest,cor1);
                   if (ok1)
                   {
                       piece1.setPosX(cor1.x);
                       piece1.setPosY(cor1.y);
                       boardTest.ajouterPiece(piece1);
                       //boardTest.print();
                       resolu = testConfig(boardTest);

                   }

               }

           }

           if (resolu)
           {
               cout << "ok j'ai trouve" << endl;
               boardTest.print();
           }
          //combine.erase (combine.begin() + curseur); //erase de index-th element of tab
          combine4.pop_back();
          curseur = combine4.size();
        }
    }


}


camelot_jr::MouveCoords toPose( int ligne, int colonne)
{
    camelot_jr::MouveCoords var;
    double z,y,x;
    x = (SXmin + SXmax) / 2.0;

    switch (ligne) {
        case 0: z = (l0min + l0max ) / 2.0 ;
                break;
        case 1: z = (l1min + l1max ) / 2.0 ;
                break;
        case 2: z = (l1min + l2max ) / 2.0 ;
                break;
        case 3: z = (l3min + l3max ) / 2.0 ;
                break;
    }

    switch (colonne) {
        case 0: y = (c0min + c0max ) / 2.0 ;
                break;
        case 1: y = (c1min + c1max ) / 2.0 ;
                break;
        case 2: y = (c1min + c2max ) / 2.0 ;
                break;
        case 3: y = (c3min + c3max ) / 2.0 ;
                break;
        case 4: y = (c4min + c4max ) / 2.0 ;
                break;
        case 5: y = (c5min + c5max ) / 2.0 ;
                break;                
    }

    var.destination.position.x = x;
    var.destination.position.y = y;
    var.destination.position.z = z;
    return var;
}