#ifndef ROISEGMENTER3D_H
#define ROISEGMENTER3D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <std_msgs/Int32MultiArray.h>

//PCL's includes
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>

//Msgs

#include <sensor_msgs/PointCloud2.h>


class RoiSegmenter3D //: public RoiSegmenter
{

public:
    RoiSegmenter3D();

private:
    ros::NodeHandle nh;

    ros::Subscriber point_cloud_sub;
    ros::Publisher point_cloud_pub;

    ros::Publisher coord_pub;

    void segment(const sensor_msgs::PointCloud2ConstPtr &);

    void distance2px(pcl::PointCloud <pcl::PointXYZRGB>);

};

#endif // ROISEGMENTER3D_H
