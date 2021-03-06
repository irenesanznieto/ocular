//#ifndef RECOGNIZERNODE_H
//#define RECOGNIZERNODE_H

//#include <ros/ros.h>
//#include "../libraries/algorithm2D.h"
//#include "../libraries/algorithm3D.h"

//#include <ocular/HandImage.h>
//#include <std_msgs/Int32.h>
//#include <ocular/EventHandler.h>

////* RecognizerNode class
///**
//* Matches the current image and pointclouds with the ones from the dataset. Its output is the ID of the recognized object
//* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
//* \date March 4th, 2014
//*/
//class RecognizerNode
//{
//public:
//    RecognizerNode();
//    ros::NodeHandle nh;
//    ros::Publisher object_pub;
//    ros::Subscriber descriptors2D_sub;

//    ros::Subscriber event_sub;

//private:
//    Algorithm2D alg2D;
//    void descriptors2D_cb(const ocular::HandImageConstPtr & );
//    void setEvent(const ocular::EventHandlerConstPtr & );

//    bool recognize;


//};

//#endif // RECOGNIZERNODE_H
