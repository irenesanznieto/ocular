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

    image_transport::Publisher image_r_pub;
    image_transport::Publisher image_l_pub;

    image_transport::Subscriber image_sub;

    ros::Subscriber coord_r_sub;
    ros::Subscriber coord_l_sub;


    void segment (const sensor_msgs::ImageConstPtr &);
    void coordinates(const std_msgs::Int32MultiArrayConstPtr &);

    std_msgs::Int32MultiArray coord;

    void left(const std_msgs::Int32MultiArrayConstPtr & );
    void right(const std_msgs::Int32MultiArrayConstPtr & );


    //This will store "left" or "right" depending on the hand
    std::string hand;

};

#endif // ROISEGMENTER2D_H
