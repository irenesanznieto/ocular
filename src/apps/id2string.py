#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from ocular.msg import RecognizedObject
from std_msgs.msg import Int16

def callback (data):

	objects=['pelota','taza']
	if data.data >=0 and len(objects) > data.data :
		print objects[data.data]
		pub.publish(objects[data.data])
	else: 
		pub.publish('NO_OBJECT_RECOGNIZED')


if __name__ == "__main__":
    pub = rospy.Publisher('final_object_name',String)
    rospy.init_node('id2string',anonymous=True)
    r=rospy.Rate(10)
    rospy.Subscriber("final_object_id", Int16, callback)
    rospy.spin()
