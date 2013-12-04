#include <iostream>
#include <ros/ros.h>
#include "../libraries/roisegmenter3D.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "ROI_SEGMENTER");

    RoiSegmenter3D rs3D;

    ros::spin();

    return 0;
}
