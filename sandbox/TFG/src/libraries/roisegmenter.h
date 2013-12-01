#ifndef ROI_SEGMENTER_H
#define ROI_SEGMENTER_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//PCL's includes
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>

//Msgs
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/PointCloud2.h>

//Image
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class RoiSegmenter
{
public:
    RoiSegmenter();

private:


    ros::NodeHandle nh;

    ros::Subscriber point_cloud_sub;
    ros::Publisher point_cloud_pub;

    ros::Publisher coord_pub;

    image_transport::ImageTransport it;

    image_transport::Publisher image_pub;
    image_transport::Subscriber image_sub;

    void segment3D (const sensor_msgs::PointCloud2ConstPtr &);
    void segment2D (const sensor_msgs::ImageConstPtr &);

    void distance2px( pcl::PointCloud <pcl::PointXYZRGB>);

    std_msgs::Int32MultiArray coord;


//    void roi3D(pcl::PointCloud <pcl::PointXYZRGB> cloud);


};
#endif //ROI_SEGMENTER_H
