#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/RoiSegmenter2DNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "ROI_SEGMENTER_2D");

    RoiSegmenter2DNode roisegmenter2D;

    ros::spin();

    return 0;
}
