//------------------------------------------------------------------------------
//-- FeatureExtractor3DNode class
//------------------------------------------------------------------------------
//--
//--  Connects the methods implemented in the FeatureExtractor3D class with the other packages using ROS topics.
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Bachelor's Thesis "In-hand object detection and tracking using 2D and 3D information"
//-- (https://github.com/irenesanznieto/ocular)
//--
//------------------------------------------------------------------------------
//-- Author: Irene Sanz Nieto
//--
//-- Released under the MIT license (more info on LICENSE.md file)
//------------------------------------------------------------------------------

#ifndef FEATUREEXTRACTOR3DNODE_H
#define FEATUREEXTRACTOR3DNODE_H

#include "../libraries/featureextractor3D.h"
#include <ros/ros.h>
#include <pcl_conversions/pcl_conversions.h>

//* FeatureExtractor3DNode class
/**
* Connects the methods implemented in the FeatureExtractor3D class with the other packages using ROS topics.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 18th, 2014
*/

class FeatureExtractor3DNode
{
public:
    /*!
    * \brief Public constructor
    *
    * Initializes the ros::Subscriber and ros::Publisher nodes.
    */
    FeatureExtractor3DNode();


    ros::NodeHandle nh;             /** NodeHandle variable to control the nodes*/
    ros::Subscriber point_cloud_sub;    /**Subscriber used to obtain the segmented point clouds from the RoiSegmenter3D node */
    ros::Publisher descriptors_pub;

private:
    FeatureExtractor3D fe3D;    /**Object of the FeatureExtractor3D class*/

    void segmented_pc_cb (const sensor_msgs::PointCloud2ConstPtr &);


};

#endif // FEATUREEXTRACTOR3DNODE_H
