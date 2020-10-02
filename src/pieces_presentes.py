#!/usr/bin/env python

import rospy
from std_msgs.msg import UInt32MultiArray 

<<<<<<< HEAD
Id = UInt32MultiArray() #tableau des identifiant present sur l'image
def markers(msg)
	for i in msg.data:
		Id.data.append(i)

rospy.init_node("Piece_presente")
rospy.Subscriber("/aruco_marker_publisher/markers_list",UInt32MultiArray,markers,queue_size = 20)
=======

Id = UInt32MultiArray() #tableau des identifiant present sur l'image



	
def markers(msg):
	Id.data = []  # effacer le tableau a chaque call
	for i in msg.data:
		Id.data.append(i)
	
		
	 


rospy.init_node("Piece_presente")
rospy.Subscriber("/aruco_marker_publisher/markers_list",UInt32MultiArray,markers,queue_size = 10)
>>>>>>> Najib
pub = rospy.Publisher("/Pieces_presentes",UInt32MultiArray,queue_size = 10)
rate = rospy.Rate(10)

while not rospy.is_shutdown():
	pub.publish(Id)
	rate.sleep()



