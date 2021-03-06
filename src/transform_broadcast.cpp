#include "Eigen/Dense"
#include "Eigen/Core"
#include "../include/GamePlay.h"
#include "../include/Transformation.h"





template<> 
tf::Transform SpatialTransform<double>::convertToTF()
{            
    tf::Matrix3x3 Mq;
    for (int i=0;i<3;i++)   for (int j=0;j<3;j++)
        Mq[i][j] = rotation(i,j);
    return tf::Transform(  Mq, tf::Vector3(position(0),position(1),position(2)));  
}

bool found_marker( const aruco_msgs::MarkerArray& msg,
                    unsigned int id,
                    aruco_msgs::Marker & marker)
{
    unsigned int nb_markers = msg.markers.size();
    for (int i=0;i<nb_markers;i++)
    {
        const aruco_msgs::Marker& m = msg.markers[i];
        if (m.id == id)
        {
            marker = m;
            return true;
        }
    }
    return false;
}   

bool found_all_markers( const aruco_msgs::MarkerArray& msg,
                        unsigned int id1, unsigned int id2,
                        aruco_msgs::Marker& marker1,    aruco_msgs::Marker& marker2)
{
    return found_marker(msg,id1,marker1) && found_marker(msg,id2,marker2);
}

// transformation du repere de la camera dans le repere map (marker1)
Transformation TCamera;


bool ref_marker_found = false;

Transformation TMarker1InCamera;

aruco_msgs::MarkerArray pieceArray;

void chatterCallback(const aruco_msgs::MarkerArray& msg)
{
    unsigned int socleMarkerId = 7;

    // la camera percoit "nb_markers" marqueurs.
    unsigned int nb_markers = msg.markers.size();
    
        
    aruco_msgs::Marker mSocle;
    
    if (found_marker(msg,7,mSocle))  // on cherche le marker de ref (socle)
    {   
        configXml("/home/najib/catkin_ws/src/camelot_jr/config.xml"); //extraction des données du fichier config xml
        //ROS_INFO("On voit le marker 7 (socle) du repere de reference  et nb_markers = %d",nb_markers);
            // on calcule le repere de la camera par rapport au repere scole.
            Transformation  T1InCamera(mSocle.pose.pose); // repere du marker socle dans le repere de la camera
            TCamera = T1InCamera.inverse();               // repere de la camera dans repere du marker socle
            ref_marker_found = true;
            pieceArray.markers.clear();
            for (int i=0;i<nb_markers;i++)
            {
                if (msg.markers[i].id != 7)
                {
                    aruco_msgs::Marker pieceMarker;

                    pieceMarker.id = msg.markers[i].id;
                    const aruco_msgs::Marker& m = msg.markers[i];
                    Transformation  Trans(m.pose.pose);
                    Transformation  TWorld = TCamera*Trans;

                    pieceMarker.pose.pose.position.x = TWorld.position(0);
                    pieceMarker.pose.pose.position.y = TWorld.position(1);
                    pieceMarker.pose.pose.position.z = TWorld.position(2);
                    pieceMarker.pose.pose.orientation.x = TWorld.rotation(0);
                    pieceMarker.pose.pose.orientation.y = TWorld.rotation(1);
                    pieceMarker.pose.pose.orientation.z = TWorld.rotation(2);
                    pieceArray.markers.push_back(pieceMarker);

                    float x = pieceArray.markers.back().pose.pose.position.x;
                    float y = pieceArray.markers.back().pose.pose.position.y;
                    float z = pieceArray.markers.back().pose.pose.position.z;
                    float xo = pieceMarker.pose.pose.orientation.x;
                    float yo = pieceMarker.pose.pose.orientation.y;
                    float zo = pieceMarker.pose.pose.orientation.z;
                    if (x<0 && x >-0.18 && y <0.13 && y > -0.08)
                    {
                        std::cout << "\nla piece " << pieceArray.markers.back().id << " est sur le plateau" << std::endl;
                        std::cout << "ligne :  " << toLigne(z) << " colonne : " << toColonne(y) << std::endl;
                        std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl << std::endl;

                    }
                
                    //ROS_INFO(" ");
                    //std::cout << "id_cube_i : " << msg.markers[i].id << std::endl;
                    //std::cout << "id_cube_back : " << pieceArray.markers.back().id << std::endl;
                    //std::cout << " position_array :\n " << "\n  x :" <<x<<"\n  y : " << y << "\n  z : " << z << std::endl; 
                   // std::cout << " orientation_piece :\n " << "\n  x :" <<xo<<"\n  y : " << yo << "\n  z : " << zo << std::endl; 
                    
                }    
            }   
    }
    else
    {
        if (ref_marker_found && nb_markers > 0 )
        {
           ROS_INFO("On voit plus le marker de ref mais la trans a deja ete calculee");
            pieceArray.markers.clear();
            for (int i=0;i<nb_markers;i++)
            {
                if (msg.markers[i].id != 7)
                {
                    aruco_msgs::Marker pieceMarker;

                    pieceMarker.id = msg.markers[i].id;
                    const aruco_msgs::Marker& m = msg.markers[i];
                    Transformation  Trans(m.pose.pose);
                    Transformation  TWorld = TCamera*Trans;

                    pieceMarker.pose.pose.position.x = TWorld.position(0);
                    pieceMarker.pose.pose.position.y = TWorld.position(1);
                    pieceMarker.pose.pose.position.z = TWorld.position(2);
                    pieceMarker.pose.pose.orientation.x = TWorld.rotation(0);
                    pieceMarker.pose.pose.orientation.y = TWorld.rotation(1);
                    pieceMarker.pose.pose.orientation.z = TWorld.rotation(2);
                    pieceArray.markers.push_back(pieceMarker);

                    float x = pieceArray.markers.back().pose.pose.position.x;
                    float y = pieceArray.markers.back().pose.pose.position.y;
                    float z = pieceArray.markers.back().pose.pose.position.z;
                    float xo = pieceMarker.pose.pose.orientation.x;
                    float yo = pieceMarker.pose.pose.orientation.y;
                    float zo = pieceMarker.pose.pose.orientation.z;
                    if (x<0 && x >-0.18 && y <0.13 && y > -0.08)
                    {
                        std::cout << "la piece " << pieceArray.markers.back().id << " est sur le plateau" << std::endl;
                    }
                    
                    //ROS_INFO(" ");
                    std::cout << "id_cube_i : " << msg.markers[i].id << std::endl;
                    //std::cout << "id_cube_back : " << pieceArray.markers.back().id << std::endl;
                    std::cout << " position_array :\n " << "\n  x :" <<x<<"\n  y : " << y << "\n  z : " << z << std::endl; 
                   // std::cout << " orientation_piece :\n " << "\n  x :" <<xo<<"\n  y : " << yo << "\n  z : " << zo << std::endl; 
                    
                    
                    
                }    
            } 
        }
        
    }
                 
    
}






int main(int argc, char** argv){

    ros::init(argc, argv, "transform_broadcaster");

    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/aruco_marker_publisher/markers", 10,chatterCallback);
    ros::Publisher pub = nh.advertise<aruco_msgs::MarkerArray>("Piece_pose_array", 10);
    ros::Rate loop_rate(10);
    
    while (ros::ok())
    {
        pub.publish(pieceArray);

        ros::spinOnce();

        loop_rate.sleep();
    }
    return 0;
};




