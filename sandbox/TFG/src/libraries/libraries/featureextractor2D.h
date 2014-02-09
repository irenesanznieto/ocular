//------------------------------------------------------------------------------
//-- FeatureExtractor2D class
//------------------------------------------------------------------------------
//--
//--  Extracts the features (descriptors) from a previously segmented image
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Bachelor's Thesis "In-hand object detection and tracking using 2D and 3D information"
//-- (https://github.com/irenesanznieto/TFG)
//--
//------------------------------------------------------------------------------
//-- Author: Irene Sanz Nieto
//--
//-- Released under the MIT license (more info on LICENSE.md file)
//------------------------------------------------------------------------------


#ifndef FEATURE_EXTRACTOR_2D_H
#define FEATURE_EXTRACTOR_2D_H

#include "roisegmenter2D.h"


//* FeatureExtractor2D class
/**
*  Extracts the features (descriptors) from a previously segmented image
*/
class FeatureExtractor2D
{
public:


/*!
    * \brief Public constructor
    *
    * 
    */
    FeatureExtractor2D();
    void extract_features(const sensor_msgs::ImageConstPtr & );

private:
    image_transport::Subscriber image_r_sub;
    image_transport::Subscriber image_l_sub;

//TODO: separate the ROS part from the actual computing part!!

    ros::NodeHandle nh;
    image_transport::ImageTransport it;

    void right(const sensor_msgs::ImageConstPtr & );
    void left(const sensor_msgs::ImageConstPtr & );

//    void save_descriptors(cv::Mat &descriptors, std::string filename);
//    void save_keypoints(std::vector <cv::KeyPoint> & keyp, std::string filename);

    std::string name;
};


#endif //FEATURE_EXTRACTOR_2D_H
