#ifndef ROISEGMENTER3D_H
#define ROISEGMENTER3D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//PCL's includes
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>

//Msgs
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Int32MultiArray.h>
#include <TFG/HandLoc.h>




class RoiSegmenter3D //: public RoiSegmenter
{

public:
    RoiSegmenter3D();

private:
    ros::NodeHandle nh;

    ros::Subscriber point_cloud_sub;
    ros::Subscriber coord_sub;

    ros::Publisher point_cloud_pub;

    ros::Publisher coord_r_pub;
    ros::Publisher coord_l_pub;

    void segment(const sensor_msgs::PointCloud2ConstPtr &);

    void distance2px(pcl::PointCloud<pcl::PointXYZ>& , pcl::PointCloud <pcl::PointXYZ>& );

    void coordinates (const TFG::HandLocConstPtr &);

    TFG::HandLoc coord;



};

#endif // ROISEGMENTER3D_H
