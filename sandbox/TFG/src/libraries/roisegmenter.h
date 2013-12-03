#ifndef ROI_SEGMENTER_H
#define ROI_SEGMENTER_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>


class RoiSegmenter
{
public:
    RoiSegmenter();

private:

    ros::NodeHandle nh;
};
#endif //ROI_SEGMENTER_H
