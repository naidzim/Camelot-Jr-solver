#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "aruco_msgs/MarkerArray.h"
#include "vector"

typedef struct {
    int id;
    geometry_msgs::Pose pose;
    geometry_msgs::Point distance;
}corCubes;

typedef struct {
    int ligne;
    int colonne;
    float** data;
}matrice;




matrice creer_matrice(int ligne, int colonne); // creation de matrice de dim (ligne,colonne)
matrice produit(matrice A, matrice B);   // produit matriciel
matrice negation(matrice A);    // retourne -A
matrice transposee (matrice A); // calculde de la transposee d'une matrice de dim (n,m)
matrice createRotMatrice(float x,float y,float z,float w); // creer matrice de rotation
matrice createTransMatrice(matrice rot,matrice pos); // creer matrice de transformation



using namespace std;


void callback(const aruco_msgs::MarkerArray::ConstPtr& msg)
{ 
    vector<corCubes> poseArray;
    corCubes pose_socle;
    corCubes pose_cube;
    
    matrice pVector = creer_matrice(3,1);
    matrice tMatrix;
    matrice rMatrix = creer_matrice(3,3);
    
    //Transformation entre le repere de l'image et le repere de la camera
    matrice tImageCamera = creer_matrice(4,4); // matrice initialier avec 0;
    tImageCamera.data[0][0] = -1.0;
    tImageCamera.data[1][2] = 1.0;
    tImageCamera.data[2][1] = 1.0;
    tImageCamera.data[3][3] = 1.0; 

    matrice tCameraSocle;
   
    // recherche du socle 
    int i = 0;
    bool trouve = false;
    while (i < msg->markers.size() && !msg->markers.empty() && trouve == false)
    {
        if (msg->markers[i].id == 7)
        {
            float xs,ys,zs;
            float x,y,z,w;
            pose_socle.id = msg->markers[i].id;
            pose_socle.pose = msg->markers[i].pose.pose;

            // matrice de transformation socle (dans l'image) -> camera
            pVector.data[0][0] = pose_socle.pose.position.x;  //veceur position
            pVector.data[1][0] = pose_socle.pose.position.y;
            pVector.data[2][0] = pose_socle.pose.position.z;
            rMatrix = creer_matrice(3,3);                    // matrice rotation init a 0
            rMatrix.data[0][0] = -1.0;
            rMatrix.data[1][2] = 1.0;
            rMatrix.data[2][1] = 1.0;

            matrice tSocleCamera = createTransMatrice(rMatrix,pVector);

            // matrice de transformation camera -> socle (matrice inverse)
            rMatrix = transposee(rMatrix);
            matrice nRMatrix = negation(rMatrix);
            matrice rpMatrice = produit(nRMatrix,pVector);
            tCameraSocle = createTransMatrice(rMatrix,pVector);
            trouve = true; // piece socle existe sur l'image 
        }
        i++;
    }
    // socle localised
    if (trouve && !msg->markers.empty())
    {
        float x,y,z,w;
        for (int j = 0; j < msg->markers.size(); j++)
        {
            if (msg->markers[j].id != 7 )
            {
                pose_cube.id = msg->markers[j].id;
                pose_cube.pose.orientation = msg->markers[j].pose.pose.orientation;
                // localisation du cubes par rapport repere du socle
                // coord dans repere socle = tCameraSocle * tImageCamera * coord dans repere Image 
                matrice cubeVectorImage = creer_matrice(4,1);
                cubeVectorImage.data[0][0] = msg->markers[j].pose.pose.position.x;
                cubeVectorImage.data[1][0] = msg->markers[j].pose.pose.position.y;
                cubeVectorImage.data[2][0] = msg->markers[j].pose.pose.position.z;
                cubeVectorImage.data[3][0] = 1;

                matrice tImageSocle = produit(tCameraSocle,tImageCamera);
                matrice posCubeMatrice = produit(tImageSocle,cubeVectorImage);
                
                pose_cube.pose.position.x = posCubeMatrice.data[0][0];
                pose_cube.pose.position.y = posCubeMatrice.data[1][0];
                pose_cube.pose.position.z = posCubeMatrice.data[2][0];

                poseArray.push_back(pose_cube);
            }
        }
    }
    if (! poseArray.empty())
    {
        ROS_INFO("id_cube : %d\n  x : %f\n  y : %f\n  z : %f\n" ,poseArray[0].id,poseArray[0].pose.position.x,poseArray[0].pose.position.y,poseArray[0].pose.position.z);
        ROS_INFO("\n  x : %f\n  y : %f\n  z : %f\n",poseArray[0].pose.orientation.x,poseArray[0].pose.orientation.y,poseArray[0].pose.orientation.z);
    }
    
}

int main(int argc,char** argv){
    ros::init(argc,argv,"position_cubes");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/aruco_marker_publisher/markers",10,callback);
    ros::spin();
    return 0;
}







matrice creer_matrice(int ligne, int colonne){
       matrice m;
       m.ligne = ligne;
       m.colonne = colonne;
       m.data = (float**)malloc(m.ligne*sizeof(float *));
       for(int i = 0; i< m.ligne; ++i){
          // initialiser les cases à 0 avec calloc
          m.data[i] = (float *)calloc(m.colonne,sizeof(float)); 
       }
       return m;
}


matrice produit(matrice A, matrice B)
{
      matrice C = creer_matrice(A.ligne, B.colonne);
      for(int I = 0; I < A.ligne; I++)
      for(int J = 0; J < B.colonne; J++)
      {
          C.data[I][J] = 0;
          for(int K = 0; K < A.colonne; K++)
          {
              C.data[I][J] += A.data[I][K] * B.data[K][J];
          }
      }
      return C;
}

matrice transposee (matrice A)
{
    matrice tA  = creer_matrice(A.colonne,A.ligne);
    for (int i = 0; i<A.ligne; i++)
    {
        for (int j=0; j<A.colonne; j++)
        {
            tA.data[j][i] = A.data[i][j];
        }
    }
    return tA;
}

matrice negation(matrice A)
{
    matrice nA = creer_matrice(A.ligne, A.colonne);
    for (int i = 0; i<A.ligne; i++)
    {
        for (int j=0; j<A.colonne; j++)
        {
            nA.data[j][i] = -  A.data[i][j];
        }
    }
    return nA;
}

matrice createRotMatrice(float x,float y,float z,float w)
{
    matrice rMatrix = creer_matrice(3,3);
    rMatrix.data[0][0] = 1 - 2*(y*y + z*z);
    rMatrix.data[0][1] = 2 * (x*y - w*z);
    rMatrix.data[0][2] = 2 * (x*z + w*z);
    rMatrix.data[1][0] = 2 * (x*y + w*z);
    rMatrix.data[1][1] = 1 - 2*(x*x + z*z);
    rMatrix.data[1][2] = 2 * (y*z - w*x);
    rMatrix.data[2][0] = 2 * (x*z - w*z);
    rMatrix.data[2][1] = 2 * (y*z + w*x);
    rMatrix.data[2][2] = 1 - 2*(x*x + y*y);
    return rMatrix;
}


matrice createTransMatrice(matrice rot,matrice pos)
{
    matrice T = creer_matrice(4,4);
    for (int i = 0; i<3;i++)
    {
        for (int j=0; j<3; j++)
        {
            T.data[i][j] = rot.data[i][j];
        }
    }
    for (int i=0; i<3; i++)
    {
        T.data[i][3] = pos.data[i][0];
        T.data[3][i] = 0;
    }
    T.data[3][3] = 1.0;
    return T;
}