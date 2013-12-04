#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>

//Image
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


class RoiSegmenter2D //: public RoiSegmenter
{
public:
    RoiSegmenter2D();

private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it;

    image_transport::Publisher image_pub;
    image_transport::Subscriber image_sub;

    ros::Subscriber coord_sub;


    void segment (const sensor_msgs::ImageConstPtr &);
    void coordinates(const std_msgs::Int32MultiArrayConstPtr &);

    std_msgs::Int32MultiArray coord;


};

#endif // ROISEGMENTER2D_H
