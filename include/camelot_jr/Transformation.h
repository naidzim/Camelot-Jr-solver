#ifndef __TRANSFORMATION__
#define __TRANSFORMATION__

#define PI 3.14159265359 

#include <ros/ros.h>
#include <aruco_msgs/MarkerArray.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>


template< typename T>
Eigen::Matrix<T,4,1> normalize( const T & A, const T & B, const T & C, const T & D)
{
    T norm = sqrt( A*A + B*B + C*C + D*D);
    Eigen::Matrix<T,4,1> out;
    out(0) = A/norm;
    out(1) = B/norm;
    out(2) = C/norm;
    out(3) = D/norm;
    return out;
}

template< typename T>
Eigen::Matrix<T,3,3> setQuaternion( const T & A, const T & B, const T & C, const T & D)
{
    // on s'assure qu'il soit de norm unité
    Eigen::Matrix<T,4,1> quat = normalize(A,B,C,D);
    T a = quat(0);
    T b = quat(1);
    T c = quat(2);
    T d = quat(3);
    
    Eigen::Matrix<T,3,3> rotation;
    rotation(0,0) = a*a +b*b -c*c - d*d;
    rotation(0,1) = 2*b*c - 2*a*d;
    rotation(0,2) = 2*a*c + 2*b*d;
    rotation(1,0) = 2*a*d + 2*b*c;
    rotation(1,1) = a*a - b*b + c*c - d*d;
    rotation(1,2) = 2*c*d - 2*a*b;
    rotation(2,0) = 2*b*d - 2*a*c;
    rotation(2,1) = 2*a*b + 2*c*d;
    rotation(2,2) = a*a - b*b - c*c + d*d;    
    
    return rotation;
}


template< typename T>
Eigen::Matrix<T,3,3> setRPY( const T & roll, const T & pitch, const T & yaw)
{
    Eigen::Matrix<T,3,3> rotation;
    const T cr = cos(roll); // ROLL
    const T sr = sin(roll);
    const T cp = cos(pitch); // PITCH
    const T sp = sin(pitch);
    const T cy = cos(yaw); // YAW
    const T sy = sin(yaw);

    rotation(0,0) = cy*cp;
    rotation(0,1) = cy*sp*sr-sy*cr;
    rotation(0,2) = cy*sp*cr+sy*sr;

    rotation(1,0) = sy*cp;
    rotation(1,1) = sy*sp*sr+cy*cr;
    rotation(1,2) = sy*sp*cr-cy*sr;

    rotation(2,0) = -sp;
    rotation(2,1) = cp*sr;
    rotation(2,2) = cp*cr;
    
    return rotation;
}

template< typename T>
Eigen::Matrix<T,3,3> setRotationX( const T & angle)
{
    Eigen::Matrix<T,3,3> rotation;
    
    rotation(0,0) = 1.0;
    rotation(0,1) = 0.0;
    rotation(0,2) = 0.0;

    rotation(1,0) = 0.0;
    rotation(1,1) = cos(angle);
    rotation(1,2) = sin(angle);

    rotation(2,0) = 0.0;
    rotation(2,1) =-sin(angle);
    rotation(2,2) = cos(angle);
    
    return rotation;
}

template< typename T>
Eigen::Matrix<T,3,3> setRotationY( const T & angle)
{
    Eigen::Matrix<T,3,3> rotation;
    
    rotation(0,0) = cos(angle);
    rotation(0,1) = 0.0;
    rotation(0,2) = sin(angle);

    rotation(1,0) = 0.0;
    rotation(1,1) = 1.0;
    rotation(1,2) = 0.0;

    rotation(2,0) =-sin(angle);
    rotation(2,1) = 0.0;
    rotation(2,2) = cos(angle);
    
    return rotation;
}

template< typename T>
Eigen::Matrix<T,3,3> setRotationZ( const T & angle)
{
    Eigen::Matrix<T,3,3> rotation;
    
    rotation(0,0) = cos(angle);
    rotation(0,1) =-sin(angle);
    rotation(0,2) = 0.0;

    rotation(1,0) = sin(angle);
    rotation(1,1) = cos(angle);
    rotation(1,2) = 0.0;

    rotation(2,0) = 0.0;
    rotation(2,1) = 0.0;
    rotation(2,2) = 1.0;
    
    return rotation;
}


template < typename T > 
class SpatialTransform
{
    public :
        SpatialTransform( )
        {
            position = Eigen::Matrix<T,3,1>::Zero();
            rotation = Eigen::Matrix<T,3,3>::Identity();
        }

        SpatialTransform( const T& x, const T& y,const T& z,
                          const T& a, const T& b, const T& c, const T& d)
        {
            position = Eigen::Matrix<T,3,1>(x,y,z);
            rotation = setQuaternion(a,b,c,d);
        }
    
        SpatialTransform(   const Eigen::Matrix<T,3,1>& pos,
                            const Eigen::Matrix<T,3,3>& rot):position(pos),rotation(rot)
        {
            
        }
        
        SpatialTransform( const geometry_msgs::Pose& msg)
        {
            rotation = setQuaternion(msg.orientation.w,msg.orientation.x,msg.orientation.y,msg.orientation.z);
            
            Eigen::Matrix<T,3,3> rot_camera;
            rot_camera(0,0) = -1.0;
            rot_camera(0,1) = 0.0;
            rot_camera(0,2) = 0.0;
            rot_camera(1,0) = 0.0;
            rot_camera(1,1) = 0.0;
            rot_camera(1,2) = 1.0;
            rot_camera(2,0) = 0.0;
            rot_camera(2,1) = 1.0;
            rot_camera(2,2) = 0.0;
            rotation = rotation*rot_camera;
        
            position(0) = msg.position.x;
            position(1) = msg.position.y;
            position(2) = msg.position.z;
        }

        tf::Transform convertToTF();
        
        SpatialTransform inverse()
        {
            SpatialTransform out;
            out.rotation = rotation.transpose();
            out.position = - rotation.transpose() * position;
            return out;
        }
        
        SpatialTransform operator* (const SpatialTransform &b) const
        {
                return SpatialTransform( position + rotation* b.position, rotation * b.rotation);
        }
        
        Eigen::Matrix<T,3,1> position;
        Eigen::Matrix<T,3,3> rotation;
};



typedef  SpatialTransform<double> Transformation;

#endif
