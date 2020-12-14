#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/UInt8MultiArray.h"


#define PI 3.1416

// Umrechnung Radian->Degree
// pi=180°
// aRadien/pi*180


uint _DataArray[6];

using namespace std;

int main(int argc, char** argv)
{
  std_msgs::UInt8MultiArray array;
  array.data = {100, 100, 100, 100, 100, 100}; // init les position des articulation

  ros::init(argc,argv,"braccio_control");
  


  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::UInt8MultiArray>("/braccio_arm/joint_angles", 6);
  
  ros::Rate loop_rate(10);

  pub.publish(array);
 ros::spinOnce();
    loop_rate.sleep();

  int numJoint = 20;
  while (ros::ok() && numJoint !=0)
  {
    
    int mouvVal ;
    std::system("clear");
    std::cout << "1: base_joint\n2: soulder_joint\n3: elbow_joint\n4: wrist_pitch_joint\n5: wrist_roll_joint\n6: sub_gripper_joint\n0: Quitter\n\n" ;
    std::cout << "Saisir le numero du Joint : " << endl;;
    std::cin >> numJoint;
    
    if (numJoint > 0 && numJoint < 7)
    {
        std::cout << "Saisir la valeur du mouvement (0 - 180): " << endl;
        std::cin >> mouvVal;
        array.data[numJoint - 1] = mouvVal;
    }
    pub.publish(array);
    ros::spinOnce();
    loop_rate.sleep();
  }
  
  

  return 0;
}