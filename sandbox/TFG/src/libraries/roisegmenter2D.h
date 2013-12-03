#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include "roisegmenter.h"

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//Image
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


class RoiSegmenter2D: public RoiSegmenter
{
public:
    RoiSegmenter2D();
    void segment(const sensor_msgs::ImageConstPtr & );

private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it;

    image_transport::Publisher image_pub;
    image_transport::Subscriber image_sub;


    void segment2D (const sensor_msgs::ImageConstPtr &);

};

#endif // ROISEGMENTER2D_H
