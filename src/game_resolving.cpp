#include "../include/GamePlay.h"
#include "ros/ros.h"
#include "ros/time.h"
#include <cstdio>
#include <string>

#include "camelot_jr/PieceAction.h" // msg type


using namespace std;


int main(int argc, char **argv)
{ 
    ros::init(argc, argv, "resolution");
    ros::Time::init(); 
    ros::NodeHandle nh("~");
    ros::Publisher speach_pub = nh.advertise<std_msgs::String>("/speech", 1000);
    ros::Publisher action_pub = nh.advertise<camelot_jr::PieceAction>("/PieceSolution", 1000);
    ros::Rate loop_rate(10);

    int Cpos, Ppos;
    nh.getParam("Cpos", Cpos);
    nh.getParam("Ppos", Ppos);

    if( ! (nh.hasParam("Cpos") && nh.hasParam("Ppos")) )
    {
        cout << "Rien saisie" << endl;
        nh.deleteParam("Cpos");
        nh.deleteParam("Ppos");
        return 1;
    }
    
       
    
else {

    std_msgs::String msg;
    int pLig, pCol, cLig, cCol;
    pLig = Ppos / 10;
    pCol = Ppos % 10;
    cLig = Cpos / 10;
    cCol = Cpos % 10; 
    Chevalier p1("Chevalier",1,cLig,cCol);
    Princesse p2("Princess",1,pLig,pCol);
    nh.deleteParam("Cpos");
    nh.deleteParam("Ppos");
    cout << "Chevalier ligne : " << cLig << " colonne : " << cCol << endl;
    cout << "Princess ligne : " << pLig << " colonne : " << pCol << endl;
    Board socle;
    vector<Piece> pieceDep;  
    pieceDep.push_back(p1); pieceDep.push_back(p2);
            fillBoard(socle,pieceDep);    // remplissage de la matrice 
            socle.print();                // affichage 
    
    /*** Position du chevalier et princess  ****/
    // Chevalier p1 ("Chevalier",1, ligne, colonne)
    // Princesse p2 ("Princess", 1 , ligne, colonne)

    
    //Chevalier p1("Chevalier",1,2,5);
    //Princesse p2("Princess",1,3,0);

    //Board socle;
    //vector<Piece> pieceDep;        // piece de debut du niveau
    vector<Piece> pieceSol;        // piece qui serviront a resoudre le niveau
    vector<Piece> pieceSolArray;   // contient les pieces à deplacer 
    vector<Piece> sortedPieces;    // tableau des pieces de solution ordonness

 // **** Acquisition des donnees ****
        aruco_msgs::MarkerArray::ConstPtr shareArray;
        shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);  // recuperer les markers une fois 
                                                                                                   // l'image est stable pour ne rater aucune piece
        aruco_msgs::MarkerArray marray = *shareArray;

    do{
        pieceDep.clear();
        pieceSol.clear();
        if (shareArray == NULL )
        { 
            cout << "shareArray null " << endl;
            return 1;
        }
        else  // shareArray != NULL
        {

    // ***** Extraction depuis l'image *******
            xtractImage(marray,pieceDep,pieceSol); 
            pieceDep.push_back(p1); pieceDep.push_back(p2);
            fillBoard(socle,pieceDep);    // remplissage de la matrice 
            socle.print();                // affichage 

            cout << "\nTaille pieceSol : " << pieceSol.size() << endl;

            ros::Duration(5,0).sleep(); // sleep() de 5 sec
        
    // ***** Recherche de solution *******
            pieceSolArray = resolution(socle,pieceSol);   // contient les pieces à deplacer 
            sortedPieces = etapeResolution(pieceSolArray); // tableau des pieces de solution ordonné

            if ( ! sortedPieces.empty() )
            {
                // construction de la phrase a envoyer au topic /speech (que le robot va prononcer)
                string toSay = "Ajouter la " + sortedPieces[0].getNom() +" à la position ";
                toSay += to_string( sortedPieces[0].getPosX() )+ " " + to_string( sortedPieces[0].getPosY() );
                toSay += " en orientation " + to_string(sortedPieces[0].getRotation());
                cout << toSay <<endl;

                // construction du message a envoyer sur le topic 
                camelot_jr::PieceAction a;
                a.nom = sortedPieces[0].getNom();
                a.ligne = sortedPieces[0].getPosX();
                a.colonne = sortedPieces[0].getPosY();
                a.rotation = sortedPieces[0].getRotation();

                action_pub.publish(a);
            
                msg.data = toSay;
                speach_pub.publish(msg);

                ros::spinOnce();
                loop_rate.sleep();
                ros::Duration(5,0).sleep(); // sleep for 10 sec 
            }

    // ***** verification de l'action de l'utilisateur/joueur *****
            bool found = false;                 // indique que la piece a ete trouvee
            while ( found == false)
            {
                shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);
                marray = *shareArray;
                pieceDep.clear();
                pieceSol.clear();
                xtractImage(marray,pieceDep,pieceSol);

                while ( !pieceDep.empty()  && !found )  // on verifie d'abord la position de la piece posée puis son orientation
                {
                    if (pieceDep[0].getNom() == sortedPieces[0].getNom())  // piece trouvee
                    {
                        if (pieceDep[0].getPosX() == sortedPieces[0].getPosX() && pieceDep[0].getPosY() == sortedPieces[0].getPosY())  // Bonne position
                        {
                            if (pieceDep[0].getRotation() == sortedPieces[0].getRotation())    // Bonne orientation
                            {
                                found = true;
                                cout << "Piece bien placee" << endl;
                                msg.data = "Pièce bien placée";
                                speach_pub.publish(msg);
                                ros::spinOnce();
                                loop_rate.sleep();
                            }
                            else
                            {
                                cout << "Piece au bon endroit mais pas à la bonne orientation " << endl;
                                msg.data = "Pièce au bon endroit mais pas à la bonne orientation" ;
                                speach_pub.publish(msg);
                                ros::spinOnce();
                                loop_rate.sleep();
                            }
                            
                        } 
                        else
                        {
                            cout << "Piece est sur le socle mais pas au bon endroit "<< endl; 
                            msg.data = "Pièce est sur le socle mais pas au bon endroit" ;
                            speach_pub.publish(msg);
                            ros::spinOnce();
                            loop_rate.sleep();
                        }
                        
                    }
                    pieceDep.erase(pieceDep.begin());
                }
                if (!found)  // le marker de la piece n'a pas été detecté à la derniere extraction 
                {
                    msg.data = "La piece n'a pas été trouvé veuillez réessayer";
                    speach_pub.publish(msg);
                    ros::spinOnce();
                    loop_rate.sleep();
                }
            }
            

        }

        shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);
        marray = *shareArray;
        pieceDep.clear();
        pieceSol.clear();
        cout << "taille de pieceSol avant extrac : " << pieceSol.size() << endl;
        xtractImage(marray,pieceDep,pieceSol);
        cout << "taille de pieceSol apres extrac : " << pieceSol.size() << endl;

    }while (! pieceSol.empty());

    cout << "fin du programme" << endl;
}

    return 0;
}
