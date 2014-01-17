#include "roisegmenter2D.h"

RoiSegmenter2D::RoiSegmenter2D(): it(nh)
{
    coord_sub=nh.subscribe <std_msgs::Int32MultiArray>("input_coord", 1, &RoiSegmenter2D::coordinates, this);

    image_sub=it.subscribe("input", 1, &RoiSegmenter2D::segment, this);
    image_pub=it.advertise("output",1);
}


void RoiSegmenter2D::segment(const sensor_msgs::ImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }


    if (!coord.data.empty())
    {
        ROS_ERROR("DEBUG: (%i,%i) (%i, %i)", coord.data[0],coord.data[1],coord.data[2],coord.data[3]);

        cv::Mat originalImage=cv_ptr->image.clone();

        int x, y, width, height;
//        try
//        {
            x=coord.data[0];
            y=coord.data[1];
            width=abs(coord.data[2]-coord.data[0]);
            height=abs(coord.data[3]-coord.data[1]);
            ROS_ERROR("DEBUG: x=%i y=%i width=%i height=%i", x, y, width, height);
//        }
//        catch

        cv::Mat croppedImage = originalImage(cv::Rect(x,y, width, height)).clone();


        cv_ptr->image=croppedImage.clone();
        image_pub.publish(cv_ptr->toImageMsg());

    }
}


void RoiSegmenter2D::coordinates(const std_msgs::Int32MultiArrayConstPtr & msg)
{
    coord=*msg;
}
