#include "Eigen/Dense"
#include "Eigen/Core"


#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64MultiArray.h"

Eigen::Matrix<double,Eigen::Dynamic,1> MGI( const Eigen::Matrix<double,3,1>& pos, double theta) // theta est l'angle par rapport à la verticale.
{
    double pi = 2*asin(1);
    double l1 = 0.125;
    double l2 = 0.125;
    double z_e = 0.072; // hauteur de l'epaule
    double h_p = 0.075; // distance entre la pince et le centre de l'aeticulation

    // on renseigne la position x,y,z, l'orientation selon l'axe vertival theta_v et selon l'axe du bras : theta_h
    double X = pos(0);
    double Y = pos(1);
    double Z = pos(2);

    double theta_v = theta *pi/180;
    double theta_h = 270*pi/180;
    // MGI 

    double x= X;
    double y = Y;
    double z = Z+h_p; // si la pince est verticale

    //  calcul de q1
    double dxy = sqrt( x*x+y*y);
    double q1= - atan2(y/dxy,x/dxy) - 5*pi/180;
    
    double q2,q3,q4,q5;

    // calcul de la distance (pince-epaule)
    double D = sqrt( x*x + y*y +(z-z_e)*(z-z_e));
    if(D> l1+l2+1e-6)   // on rajoute le 1e-6 pour gérer le cas bras tendu
    {
        std::cerr<<"ERRROR POINT TROP LOIN"<<std::endl;
        std::cerr<<"D = "<<D<<std::endl;
    }
    else
    {
        double cos3 = (l1*l1+l2*l2-D*D) / (2*l1*l2);
        if (cos3<-1)
        {
            std::cout<<"l'angle du coude est mal conditionné : cos3 = "<< cos3<<" supposé égal à -1 maintenant"<<std::endl;
            cos3 = -1;
            
        }
        //q3 = acos(cos3) - pi/2;
        q3 = acos(cos3);
        double alpha = (l1*l1+D*D-l2*l2) / (2*l1*D);
        if (alpha>1)    
        {
            std::cout<<" alpha est mal conditionné : alpha = "<< alpha <<" supposé égal à 1 maintenant"<<std::endl;
            alpha = 1;            
        }
        if (alpha<-1)    
        {
            std::cout<<" alpha est mal conditionné : alpha = "<< alpha <<" supposé égal à -1 maintenant"<<std::endl;
            alpha = -1;            
        }        
        //q2 = pi/2- (asin ( (z-z_e)/D) - acos(alpha));
        //q2 = pi/2 + (asin ( (z-z_e)/D) + acos(alpha));
        q2 = pi - q3 + pi/2 - 15*pi/180;
        //q4 = theta_h - (q2+q3);  
        q4 = 180*pi/180 ;
        q5 = theta_v - q1;
    }
    Eigen::Matrix<double,Eigen::Dynamic,1> out(5);
    out(0) = q1;
    out(1) = q2;
    out(2) = q3;
    out(3) = q4;
    out(4) = q5;
//     out(5) = 0;

    std::cout << q1 << std::endl << q2 << std::endl << q3 << std::endl << q4 << std::endl << q5 << std::endl;
    return out ;
}



int main(int argc, char** argv){

    double pi = 2*asin(1);

    ros::init(argc, argv, "inverse_braccio");
    ros::NodeHandle nh;

    ros::Publisher pub_gazebo = nh.advertise<std_msgs::Float64MultiArray>("/braccio_arm/joint_angles", 10);
    ros::Rate loop_rate(10);

    Eigen::Matrix<double,3,1> pos;
    pos(0) = 0.150000;
    pos(1) = -0.160000;
    pos(2) = 0.073893;
    double theta = 90;


    Eigen::Matrix<double,Eigen::Dynamic,1> angle_test = MGI(pos,theta);
    std_msgs::Float64MultiArray array;
    array.data = {1.5, 1.5, 1.5, 1.5, 1.5, 1.5}; // init les position des articulation

    int i = 0;
    
    array.data[0] = angle_test(0);
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    array.data[3] = angle_test(3);
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    array.data[2] = angle_test(2);
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    array.data[1] = angle_test(1);
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    array.data[5] = 0;
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    array.data[1] = pi/2;
    pub_gazebo.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
    ros::Duration(0.5).sleep();

    loop_rate.sleep();
    
    return 0;
};