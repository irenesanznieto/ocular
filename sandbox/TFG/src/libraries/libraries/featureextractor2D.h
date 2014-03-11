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
#include <TFG/HandImage.h>


//* FeatureExtractor2D class
/**
*  Extracts the features (descriptors) from a previously segmented image
*/
class FeatureExtractor2D
{
public:


    /*!
    * \brief Public constructor
    */
    FeatureExtractor2D();

    TFG::HandImage extract_features(const TFG::HandImageConstPtr & );   /**Extracts the 2D descriptors from the segmented input image using the ORB algorithm */

    sensor_msgs::Image get_image_with_keypoints();

private:

    sensor_msgs::Image image_with_keypoints;

};


#endif //FEATURE_EXTRACTOR_2D_H
