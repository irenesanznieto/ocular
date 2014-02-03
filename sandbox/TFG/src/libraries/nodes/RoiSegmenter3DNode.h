#ifndef ROISEGMENTER3DNODE_H
#define ROISEGMENTER3DNODE_H

#include "../libraries/roisegmenter3D.h"

//* RoiSegmenter3DNode class
/**
* This class connects the methods implemented in the RoiSegmenter3D class with the other packages through ROS nodes.
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
    ros::Subscriber coord_sub;  /**Subscriber used to obtain the TFG::HandLoc messages*/
    ros::Publisher point_cloud_pub; /**Publisher used to publish the resulting segmented point cloud*/
    ros::Publisher coord_pub;   /**Publisher used to publish the 2D ROI coordinates*/


    RoiSegmenter3D roiSegmenter3D;       /**Object of the RoiSegmenter3D class*/


    /*!
    * \brief Callback function that extracts and publishes the 3D ROI from the original point cloud using a function of the RoiSegmenter3D object
    */
    void point_cloud_cb (const sensor_msgs::PointCloud2ConstPtr &);


    /*!
    * \brief Callback function that extracts and publishes the 2D ROI's coordinates using a function of the RoiSegmenter3D object
    */
    void hand_location_cb (const TFG::HandLocConstPtr &);


};

#endif // ROISEGMENTER3DNODE_H
