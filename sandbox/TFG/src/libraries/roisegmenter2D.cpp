#include "roisegmenter2D.h"

RoiSegmenter2D::RoiSegmenter2D(): it(nh)
{
    coord_r_sub=nh.subscribe <std_msgs::Int32MultiArray>("input_r_coord", 1, &RoiSegmenter2D::right, this);
    coord_l_sub=nh.subscribe <std_msgs::Int32MultiArray>("input_l_coord", 1, &RoiSegmenter2D::left, this);

    image_sub=it.subscribe("input", 1, &RoiSegmenter2D::segment, this);

    image_l_pub=it.advertise("output_l",1);
    image_r_pub=it.advertise("output_r",1);

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
//        ROS_ERROR("DEBUG: P1: (%i,%i)  P2: (%i, %i)", coord.data[0],coord.data[1],coord.data[2],coord.data[3]);

        cv::Mat originalImage=cv_ptr->image.clone();
        cv::flip(originalImage, originalImage,1);

        cv::Point p1(coord.data[0], coord.data[1]);
        cv::Point p2(coord.data[2], coord.data[3]);
        cv::Mat croppedImage=originalImage(cv::Rect(p1, p2));

        cv_ptr->image=croppedImage.clone();

        if(this->hand=="right")
            image_r_pub.publish(cv_ptr->toImageMsg());
        else if(this->hand=="left")
            image_r_pub.publish(cv_ptr->toImageMsg());

    }
}

void RoiSegmenter2D::right(const std_msgs::Int32MultiArrayConstPtr & msg)
{
    this-> hand="right";
    this->coordinates(msg);
}

void RoiSegmenter2D::left(const std_msgs::Int32MultiArrayConstPtr & msg)
{
    this-> hand="left";
    this->coordinates(msg);
}


void RoiSegmenter2D::coordinates(const std_msgs::Int32MultiArrayConstPtr & msg)
{
    coord=*msg;
}
