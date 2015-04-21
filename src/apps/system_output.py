#!/usr/bin/env python

import roslib; roslib.load_manifest('ocular')
import rospy
from collections import Counter
import operator
from ocular.msg import *
from std_msgs.msg import Int16
import numpy as np


def frequency_counter(a):
    c = Counter(a)
    return c.values(),  c.keys()


def decision(v2d, k2d, v3d, k3d):

    # if there are any -1s they are relocated to the beginning of the list:
    if k2d[len(k2d) - 1] == -1:
        k2d.insert(0, k2d.pop(len(k2d) - 1))
        v2d.insert(0, v2d.pop(len(k2d) - 1))
    if k3d[len(k3d) - 1] == -1:
        k3d.insert(0, k3d.pop(len(k3d) - 1))
        v3d.insert(0, v3d.pop(len(k3d) - 1))

    # find max_id:

    if k2d[len(k2d) - 1] >= k3d[len(k3d) - 1]:
        max_object_id = k2d[len(k2d) - 1]
    else:
        max_object_id = k3d[len(k3d) - 1]

    # print max_object_id

    for i in range(-1, max_object_id + 1):
        #print (k2d, k3d,i)
        #print (len(k2d), len(k3d), i)
        if (len(k2d) - 1) <= i:
            k2d.append(i)
            v2d.append(0)
        else:
            if k2d[i + 1] != i:
                k2d.insert(i + 1, i)
                v2d.insert(i + 1, 0)
        if (len(k3d) - 1) <= i:
            k3d.append(i)
            v3d.append(0)
        else:
            if k3d[i + 1] != i:
                k3d.insert(i + 1, i)
                v3d.insert(i + 1, 0)
        #print (k2d[i], k3d[i],i,"\n")
        # print(k2d, k3d,i)#, v2d , v3d)

        if len(v2d) == len(v3d):
            values = np.multiply(0.5, v2d) + np.multiply(0.5, v3d)
            keys = k2d
            max_value = (max(xrange(len(values)), key=values.__getitem__))
            #print (v2d, v3d, values)
            #print ('Final decision: ', keys[max_value])

            ret = SystemOutput()
            ret.id_2d_plus_3d = keys[max_value]
            ret.id_2d = k2d[max(xrange(len(values)), key=v2d.__getitem__)]
            ret.id_3d = k3d[max(xrange(len(values)), key=v3d.__getitem__)]
            return ret

        else:
            print 'wrong len'


def callback(data):
    iterations = 30

    if not hasattr(callback, "counter"):
        callback.counter = 0  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f2d"):
        callback.f2d = []  # it doesn't exist yet, so initialize it

    if not hasattr(callback, "f3d"):
        callback.f3d = []  # it doesn't exist yet, so initialize it

    callback.counter += 1

    if callback.counter <= iterations:
        # add the new data to the lists
        callback.f2d.append(data.object_id[0])
        callback.f3d.append(data.object_id[1])

        if all([callback.counter == iterations,
               len(callback.f3d) > 0,
               len(callback.f2d) > 0]):
            # obtain the frequency of each element in the lists
            v2d, k2d = (callback.f2d)
            v3d, k3d = frequency_counter(callback.f3d)

            # obtain index of maximum element
            max2d = (max(xrange(len(v2d)), key=v2d.__getitem__))
            max3d = (max(xrange(len(v3d)), key=v3d.__getitem__))

            # print object_id 2D and 3D
            # print('2D ', k2d[max2d]) #,v2d ,k2d)
            # print('3D ', k3d[max3d]) #, v3d ,k3d)

            # decide final object & publish it
            pub.publish(decision(v2d, k2d, v3d, k3d))

            # clear lists and counter
            callback.f2d = []
            callback.f3d = []
            callback.counter = 0


if __name__ == "__main__":
    pub = rospy.Publisher('final_object_id', SystemOutput)
    rospy.init_node('system_output', anonymous=True)
    r = rospy.Rate(10)
    rospy.Subscriber("object_id", RecognizedObject, callback)
    rospy.spin()
