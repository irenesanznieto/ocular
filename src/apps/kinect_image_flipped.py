#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import Image
from subprocess import call
import os
import fnmatch
import sys
import numpy as np
from ocular.msg import RecognizedObject
from std_msgs.msg import Int16
import cv2
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image_topic_2",Image)

    cv2.namedWindow("Kinect Raw Image", 1)
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/camera/rgb/image_color",Image,self.callback)

  def callback(self,data):
  	try:
		cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
	except CvBridgeError, e:
		print e

	data_flipped = cv2.flip(cv_image, 1)
#    (rows,cols,channels) = cv_image.shape
#    if cols > 60 and rows > 60 :
#      cv2.circle(cv_image, (50,50), 10, 255)
	cv2.imshow("Kinect Raw Image", data_flipped)
	cv2.waitKey(3)

	try:
		self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
	except CvBridgeError, e:
		print e



def main(args):
  ic = image_converter()
  rospy.init_node('image_converter', anonymous=True)
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print "Shutting down"
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
    
    
#def callback (data):


#	cv2.imshow("Raw input image", data) #_flipped)
#	cv2.waitkey()


#def listener():
#        rospy.init_node('kinect_image_flipped',anonymous=True)
#        r=rospy.Rate(10)
#        rospy.Subscriber("/camera/rgb/image_color", Image, callback)
#        rospy.spin()

#if __name__=='__main__':
#    listener()
#    

