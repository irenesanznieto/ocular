#ifndef ROISEGMENTER3D_H
#define ROISEGMENTER3D_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>

//PCL's includes
//#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>

//Msgs
#include <sensor_msgs/PointCloud2.h>
#include <TFG/HandLocPx.h>
#include <TFG/HandLoc.h>

//* Class RoiSegmenter3D
/**
* This class segments an input point cloud and extracts the Region Of Interest
*  
*/



class RoiSegmenter3D 
{

public:

/*!
    * \brief Public constructor
    */
    
    RoiSegmenter3D();

private:
    ros::NodeHandle nh;/** @todo CHANGE THIS TO A ROISEGMENTER3DNODE! */

    ros::Subscriber point_cloud_sub; /** @todo CHANGE THIS TO A ROISEGMENTER3DNODE! */
    ros::Subscriber coord_sub; /** @todo CHANGE THIS TO A ROISEGMENTER3DNODE! */

    ros::Publisher point_cloud_pub; /** @todo CHANGE THIS TO A ROISEGMENTER3DNODE! */

    ros::Publisher coord_pub; /** @todo CHANGE THIS TO A ROISEGMENTER3DNODE! */
    
    /*!
    * \brief Method that segments the point cloud using a given center and fixed limits. 
    *
    * In this case, there are two segmented regions (both the right and left hands). The point cloud of interest is a cube with fixed dimensions extracted from the original point cloud. 
    */

    void segment(const sensor_msgs::PointCloud2ConstPtr &);/** @todo change the param to sensor_msgs::PointCloud2 for easier testing */

/*!
    * \brief Method that transforms the 3D world coordinates to pixels
    *
    * It is used to determine the limits of the 2D ROI. 
    */
    
    void distance2px(pcl::PointCloud<pcl::PointXYZ>& , pcl::PointCloud <pcl::PointXYZ>& );


    void coordinates (const TFG::HandLocConstPtr &);/** @todo Is this method really used?? */

    TFG::HandLoc coord;/** @todo Is this variable really used?? */



};

#endif // ROISEGMENTER3D_H
