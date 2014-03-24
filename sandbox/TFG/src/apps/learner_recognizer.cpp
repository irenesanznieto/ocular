#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/LearnerRecognizerNode.h"


int main (int argc,char* argv[])
{
    ros::init(argc, argv, "LEARNER");

    LearnerRecognizerNode learner_recognizer;

    ros::spin();

    return 0;
}
