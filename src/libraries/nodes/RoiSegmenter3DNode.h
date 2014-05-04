//------------------------------------------------------------------------------
//-- RoiSegmenter3DNode class
//------------------------------------------------------------------------------
//--
//--  Connects the methods implemented in the RoiSegmenter3D class with the other packages using ROS topics.
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


#ifndef ROISEGMENTER3DNODE_H
#define ROISEGMENTER3DNODE_H

#include "../libraries/roisegmenter3D.h"
#include <ocular/EventHandler.h>
#include <pcl_conversions/pcl_conversions.h>

//* RoiSegmenter3DNode class
/**
* Connects the methods implemented in the RoiSegmenter3D class with the other packages using ROS topics.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 3rd, 2014
*/
class RoiSegmenter3DNode
{
public:

    /*!
    * \brief Public constructor
    *
    * Initializes the ros::Subscriber and ros::Publisher nodes. The topics specified in there are used as variables that are changed in the launch file
    */
    RoiSegmenter3DNode();

private:

    ros::NodeHandle nh;             /** NodeHandle variable to control the nodes*/
    ros::Subscriber point_cloud_sub;    /**Subscriber used to obtain the point clouds from the RGB-D sensor*/
    ros::Subscriber coord_sub;  /**Subscriber used to obtain the ocular::HandLoc messages*/
    ros::Publisher point_cloud_pub; /**Publisher used to publish the resulting segmented point cloud*/
    ros::Publisher coord_pub;   /**Publisher used to publish the 2D ROI coordinates*/

    ros::Subscriber hand;  /**Subscriber used to obtain the hand being used in the software*/

    RoiSegmenter3D roiSegmenter3D;       /**Object of the RoiSegmenter3D class*/


    /*!
    * \brief Callback function that extracts and publishes the 3D ROI from the original point cloud using a function of the RoiSegmenter3D object
    */
    void point_cloud_cb (const
        pcl::PCLPointCloud2ConstPtr &);


    /*!
    * \brief Callback function that extracts and publishes the 2D ROI's coordinates using a function of the RoiSegmenter3D object
    */
    void hand_location_cb (const ocular::HandLocConstPtr &);


    void hand_name_cb(const ocular::EventHandlerConstPtr &);
};

#endif // ROISEGMENTER3DNODE_H
