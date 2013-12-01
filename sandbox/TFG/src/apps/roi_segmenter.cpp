#include <iostream>
#include <ros/ros.h>
//#include "../libraries/roisegmenter2D.h"
//#include "../libraries/roisegmenter3D.h"
#include"../libraries/roisegmenter.h"

int main (int argc,char* argv[])
{
    ros::init(argc, argv, "ROI_SEGMENTER");

//    RoiSegmenter3D rs3D;
//    RoiSegmenter2D rs2D;

    RoiSegmenter roisegmenter;

    ros::spin();

    return 0;
}
