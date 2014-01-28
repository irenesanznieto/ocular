#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//Image
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <TFG/HandLocPx.h>
#include <TFG/HandImage.h>

class RoiSegmenter2D //: public RoiSegmenter
{
public:
    RoiSegmenter2D();

private:
    ros::NodeHandle nh;
//    image_transport::ImageTransport it;

    ros::Publisher image_pub;

    ros::Subscriber image_sub;

    ros::Subscriber coord_sub;


    void segment (const TFG::HandImageConstPtr &);
    void coordinates(const TFG::HandLocPxConstPtr &);

    TFG::HandLocPx coord;


    //used to check if x and y of the square is out of bounds of the screen's limits ;)
    void checkLimits(int & , int& );



};

#endif // ROISEGMENTER2D_H
