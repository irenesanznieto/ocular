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
    iterations=10

    if not hasattr(callback, "counter"):
        callback.counter = 0  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f2D"):
        callback.f2D=[]  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f3D"):
        callback.f3D=[]  # it doesn't exist yet, so initialize it

    callback.counter += 1

   # print "counter: ",callback.counter

    if callback.counter<=iterations:
        callback.f2D.append(data.object_id[0]);
        callback.f3D.append(data.object_id[1]);

        if callback.counter == iterations:
            values, keys=frequency_counter(callback.a)
            print(values, keys)
            max_it = (max(xrange(len(values)),key=values.__getitem__))
            print('Max frequency: %d', keys[max_it])

            pub.publish(keys[max_it])

            callback.a = []
            callback.counter = 0



if __name__ == "__main__":
    pub = rospy.Publisher('output',Int16, queue_size=10)
    rospy.init_node('system_output',anonymous=True)
    r=rospy.Rate(10)
    rospy.Subscriber("object_id", RecognizedObject, callback)
    rospy.spin()