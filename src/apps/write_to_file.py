#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from subprocess import call
import os
import fnmatch
import sys

#def callback (data):
#    rospy.loginfo(rospy.get_caller_id()+"I heard %s", data.data)


#def listener():

#        rospy.init_node('listener',anonymous=True)
#        r=rospy.Rate(10)

#        rospy.Subscriber("/TFG/whatever", String, callback)
#        rospy.spin()



if __name__=='__main__':

#        call(['ls'])
#        matches=[]
#        for root, dirnames, filenames in os.walk('src'):
#            for filename in fnmatch.filter(filenames, 'output.txt'):
#                matches.append(os.path.join(root, filename))

    for  root, dir, files in os.walk('.'):                      #retrieve all files and folders in the current folder
        for d in dir:
#            print d
            if d == 'ocular':                                   #if one of them is called ocular
                d_abs=os.path.join(root,d)                      #store the absolute path to the folder in d_abs
#                print d_abs

                for root_o, dir_o, files_o in os.walk(d_abs):   #retrieve all files inside the path to the oculus folder
                    for d_o in dir_o:                           #search for a folder within
#                        print d_o
                        if d_o=='data':                         #if the folder is called data
                            absolute_path=os.path.join(d_abs,d_o)       #print the absolute path to that folder!
#                            print absolute_path

    absolute_path+='/'
    if len(sys.argv)==2:
        print 'using file from args'
        path_file=absolute_path+sys.argv[1]
    else:
        if len(sys.argv)==1:
            print 'using default file'
            path_file=absolute_path+'output.txt'
        else:
            print 'usage: exec name_file or exec'


    f=file(path_file, 'w')
    f.write('jelou again!')
#        listener()
