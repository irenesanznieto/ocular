import rospy
from std_msgs.msg import String

def callback(data):
	objects=['pelota','taza']
	if data >=0:
		pub.publish(objects[data])
	else: 
		pub.publish('no_object')


if __name__ == "__main__":
    pub = rospy.Publisher('final_object_name',String)
    rospy.init_node('id2string',anonymous=True)
    r=rospy.Rate(10)
    rospy.Subscriber("final_object_id", RecognizedObject, callback)
    rospy.spin()
