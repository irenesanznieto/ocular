#include <iostream>
#include <ros/ros.h>
#include "../libraries/nodes/RoiSegmenter3DNode.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "ROI_SEGMENTER");

    RoiSegmenter3DNode rs3D;

    ros::spin();

    return 0;
}
