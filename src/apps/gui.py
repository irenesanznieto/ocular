#!/usr/bin/python

import rospy
from std_msgs.msg import String
from subprocess import call
import os
import fnmatch
import sys
from ocular.msg import *
import time
import cv2
import cv
import numpy as np
		

def callback(data):

	img=np.zeros((250,500,3), np.uint8)
	
	#system output 
	font=cv.InitFont(cv.CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0,thickness=2)
	cv.PutText(cv.fromarray(img), "System output", (20,50), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), "2D + 3D", (20,100), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), ":", (350,75), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), str(data.id_2d_plus_3d), (450,75), font, (255, 255, 255))
	

		
	
	#2d 
	cv.PutText(cv.fromarray(img), "2D", (20,150), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), ":", (350,150), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), str(data.id_2d), (450,150), font, (255, 255, 255))
	
	#3d 
	cv.PutText(cv.fromarray(img), "3D", (20,200), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), ":", (350,200), font, (255, 255, 255))
	cv.PutText(cv.fromarray(img), str(data.id_3d), (450,200), font, (255, 255, 255))

	cv2.imshow("SYSTEM OUTPUT", img)
	cv2.waitKey(3)

def main():

#	a=SystemOutput()
#	a.id_2d=2
#	a.id_3d=3
#	a.id_2d_plus_3d=0
#	callback(a)
#	time.sleep(3)
		
	cv2.namedWindow("SYSTEM OUTPUT", 1)
	rospy.init_node('gui_demo',anonymous=True)
	r=rospy.Rate(10)
	rospy.Subscriber("final_object_id", SystemOutput, callback)
	rospy.spin()
	
if __name__ == '__main__':
    main() 


