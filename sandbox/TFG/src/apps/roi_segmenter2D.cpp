#include <iostream>
#include <ros/ros.h>
#include "../libraries/roisegmenter2D.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "ROI_SEGMENTER_2D");

    RoiSegmenter2D rs2D;

    ros::spin();

    return 0;
}
