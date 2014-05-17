#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from subprocess import call
import os
import fnmatch
import sys
import numpy as np
from ocular.msg import RecognizedObject


def callback (data):

     f=file(path_file, 'a')

     for i in range(len(data.object_id)):
		 sum=str(data.object_id[i])+' '+str(data.ratio[i])+'\n'
		 f.write(sum)

#    for i in range(len(data.object_id)):
#        np.add(matrix, ([data.object_id[i], data.ratio[i]] ) )

#    np.append(matrix, [0, 2])
#    print matrix


def listener():

        rospy.init_node('writer2file',anonymous=True)
        r=rospy.Rate(10)

        rospy.Subscriber("object_id", RecognizedObject, callback)
        rospy.spin()

def pathfinder():

    for root, dir, files in os.walk('.'): #retrieve all files and folders in the current folder
            for d in dir:
    # print d
                if d == 'ocular': #if one of them is called ocular
                    d_abs=os.path.join(root,d) #store the absolute path to the folder in d_abs
    # print d_abs

                    for root_o, dir_o, files_o in os.walk(d_abs): #retrieve all files inside the path to the oculus folder
                        for d_o in dir_o: #search for a folder within
    # print d_o
                            if d_o=='data': #if the folder is called data
                                absolute_path=os.path.join(d_abs,d_o) #print the absolute path to that folder!
    # print absolute_path

    absolute_path+='/'
    path_file=absolute_path+'test.txt'
#    if len(sys.argv)==2:
#        print 'using file from args'
#        path_file=absolute_path+sys.argv[1]
#    else:
#        if len(sys.argv)==1:
#            print 'using default file'
#            path_file=absolute_path+'test.txt'
#        else:
#            print 'usage: exec name_file or exec'

    return path_file


path_file=pathfinder()
#matrix=np.zeros((1,2))

if __name__=='__main__':

#   print path_file

#   data=RecognizedObject()

#   data.object_id[0]=20
#   data.object_id[1]=30


#   data.ratio[0]=0.3
#   data.ratio[1]=0.8

#   callback(data)

    listener()
