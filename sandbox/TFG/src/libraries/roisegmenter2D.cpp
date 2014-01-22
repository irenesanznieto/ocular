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

//        Circle to check the position of the hands:
//        cv::circle(cv_ptr->image, cv::Point(coord.data[0]+abs(coord.data[0]-coord.data[2])/2, coord.data[1]+abs(coord.data[1]-coord.data[3])/2), 10, CV_RGB(255,0,0), 10);

        cv::Mat originalImage=cv_ptr->image.clone();

        int x1=coord.data[0];
        int y1=coord.data[1];
        int x2=coord.data[2];
        int y2=coord.data[3];

        RoiSegmenter2D::checkLimits(x1, y1);
        RoiSegmenter2D::checkLimits(x2,y2);

        cv::Point p1(x1,y1);
        cv::Point p2(x2,y2);


        cv::Mat croppedImage=originalImage(cv::Rect(p2, p1));

        cv_ptr->image=croppedImage.clone();


        cv::flip(cv_ptr->image,cv_ptr->image, 1);

        if(this->hand=="right")
            image_r_pub.publish(cv_ptr->toImageMsg());
        else if(this->hand=="left")
            image_l_pub.publish(cv_ptr->toImageMsg());

    }
}

void RoiSegmenter2D::checkLimits(int & x, int& y)
{

    if (x>640)
        x=640;
    else if (x<0)
        x=0;

    if(y>480)
        y=480;
    else if(y<0)
        y=0;
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
