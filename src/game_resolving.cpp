#include "../include/GamePlay.h"
#include "ros/ros.h"
#include "ros/time.h"
#include <cstdio>

#include "camelot_jr/PieceAction.h" // msg type


using namespace std;







void chatterCallback(const aruco_msgs::MarkerArray& msg)  // extraires les données de marker array
{
   

    vector<Piece> pieceDep;    // tableau des piece de depart
    vector<Piece> pieceSol;    // tableau des pieces solution (necessaire pour la fonction resolution)
    aruco_msgs::MarkerArray marray = msg;    
    xtractImage(marray,pieceDep,pieceSol);

    


    
    for (int i = 0; i<pieceDep.size(); i++)
    {
       int ligne = pieceDep[i].getPosX();
        cout << "nom : " <<pieceDep[i].getNom() << "\n ligne : " <<  ligne <<"\n Colonne : "<< pieceDep[i].getPosY() << endl;  
        cout << " rot : " << pieceDep[i].getRotation() << endl;
    }
    pieceDep.clear();
    pieceSol.clear();

    
    
}

int main(int argc, char **argv)
{
// Ajouter un flag si solution est trouvée
// verifier que piece sol est vide et solution trouvée
// 2 pieces bleues 
    ros::init(argc, argv, "resolution");
    ros::Time::init();
    std_msgs::String msg;

    ros::NodeHandle nh;
    ros::Publisher speach_pub = nh.advertise<std_msgs::String>("/speech", 1000);
    ros::Publisher action_pub = nh.advertise<camelot_jr::PieceAction>("/PieceSolution", 1000);
    ros::Rate loop_rate(10);
   
   // aruco_msgs::MarkerArray::ConstPtr shareArray;
   // shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);  // recuperer les markers une fois l'image est stable pour ne rater aucune piece
    
    /*** Position du chevalier et princess  ****/
    // Chevalier p1 ("Chevalier",1, ligne, colonne)
    // Princesse p2 ("Princess", 1 , ligne, colonne)
    Chevalier p1("Chevalier",1,2,5);
    Princesse p2("Princess",1,3,0);

    Board socle;
    vector<Piece> pieceDep;        // piece de debut du niveau
    vector<Piece> pieceSol;        // oiece qui serviront a resoudre le niveau
    vector<Piece> pieceSolArray;   // contient les pieces à deplacer 
    vector<Piece> sortedPieces;    // tableau des pieces de solution ordonness
 

    do{

        // **** Acquisition des donnees ****
        aruco_msgs::MarkerArray::ConstPtr shareArray;
        shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);  // recuperer les markers une fois 
                                                                                                   // l'image est stable pour ne rater aucune piece
        aruco_msgs::MarkerArray marray = *shareArray;

        if (shareArray != NULL)
        {

    // ***** Extraction depuis l'image *******
            aruco_msgs::MarkerArray marray = *shareArray;
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
        xtractImage(marray,pieceDep,pieceSol);

    }while (! pieceSol.empty());


    /*if (shareArray != NULL ) 
    {
        
        aruco_msgs::MarkerArray marray = *shareArray;

        xtractImage(marray,pieceDep,pieceSol);  
     
        

        pieceDep.push_back(p1);
        pieceDep.push_back(p2);
        fillBoard(socle,pieceDep);    // remplissage de la matrice 
        socle.print();                // affichage 

        cout << "\nTaille pieceSol : " << pieceSol.size() << endl;

        for (int i=0;i<pieceSol.size(); i++)
        {
            cout << "\t" << pieceSol[i].getNom() << " (" << pieceSol[i].getPosX() << "," << pieceSol[i].getPosY() << ") r" << pieceSol[i].getRotation() << endl;
        }
        ros::Duration(5,0).sleep(); // sleep() de 5 sec
        
        vector<Piece> pieceSolArray = resolution(socle,pieceSol);   // contient les pieces à deplacer 
        
        vector<Piece> sortedPieces = etapeResolution(pieceSolArray); // tableau des pieces de solution ordonné


        
        while ( ! sortedPieces.empty())
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
            ros::Duration(10,0).sleep(); // sleep for 10 sec 
            

            // verification de l'action de l'utilisateur/joueur
            shareArray = ros::topic::waitForMessage<aruco_msgs::MarkerArray>("/Piece_pose_array",nh);
            marray = *shareArray;
            pieceDep.clear();
            pieceSol.clear();
            xtractImage(marray,pieceDep,pieceSol);
            cout << "taille de pieceDep : " << pieceDep.size() << endl;
            bool found = false;
            while ( !pieceDep.empty() && found==false)  // on verifie d'abord la position de la piece posée puis son orientation
            {
                if (pieceDep[0].getNom() == sortedPieces[0].getNom())
                {
                    if (pieceDep[0].getPosX() == sortedPieces[0].getPosX() && pieceDep[0].getPosY() == sortedPieces[0].getPosY())
                    {
                        if (pieceDep[0].getRotation() == sortedPieces[0].getRotation())
                        {
                            
                            found = true;
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
            else // si la piece est bien placé on passe a la suivante
            {
                sortedPieces.erase(sortedPieces.begin()); // supression de la premiere piece solution pour passer a celle qui suit
            }
             
        }

        msg.data = "Vous avez réussi";
        speach_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();

    }*/


    cout << "fin du programme" << endl;

    return 0;
}
