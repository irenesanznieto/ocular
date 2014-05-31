#!/usr/bin/env python

import rospy
from collections import Counter
import operator
from ocular.msg import RecognizedObject
from std_msgs.msg import Int16


def frequency_counter(a):
    c=Counter(a)
    return c.values(),  c.keys()

def callback(data):
    iterations=30

    if not hasattr(callback, "counter"):
        callback.counter = 0  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f2d"):
        callback.f2d=[]  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f3d"):
        callback.f3d=[]  # it doesn't exist yet, so initialize it

    callback.counter += 1



    if callback.counter<=iterations:
    	#add the new data to the lists
        callback.f2d.append(data.object_id[0]);
        callback.f3d.append(data.object_id[1]);


        if callback.counter == iterations:
        	#obtain the frequency of each element in the lists
            v2d, k2d=frequency_counter(callback.f2d)
            v3d, k3d=frequency_counter(callback.f3d)

			#obtain index of maximum element
            max2d = (max(xrange(len(v2d)),key=v2d.__getitem__))
            max3d = (max(xrange(len(v3d)),key=v3d.__getitem__))
            
            #print object_id 2D and 3D 
            print('2D  Max frequency: ', k2d[max2d]) #,v2d ,k2d)
            print('3D  Max frequency: ', k3d[max3d]) #, v3d ,k3d)

			#decide final object & publish it
			#values=0.6*v2d + 0.4*v3d
			#max_index = (max(xrange(len(values)),key=values.__getitem__))
            #pub.publish(keys[max_it])


			#clear lists and counter
            callback.f2d = []
            callback.f3d = []
            callback.counter = 0



if __name__ == "__main__":
    pub = rospy.Publisher('output',Int16)
    rospy.init_node('system_output',anonymous=True)
    r=rospy.Rate(10)
    rospy.Subscriber("object_id", RecognizedObject, callback)
    rospy.spin()
