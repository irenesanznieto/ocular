#ifndef ROI_SEGMENTER_H
#define ROI_SEGMENTER_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>


//PCL's includes
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

//Msgs
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/PointCloud2.h>

class RoiSegmenter
{
public:
    RoiSegmenter();

private:


    ros::NodeHandle nh;
    ros::Subscriber point_cloud_sub;
    ros::Publisher coord_pub;

    void distance2px(const sensor_msgs::PointCloud2ConstPtr &);

};
#endif //ROI_SEGMENTER_H
