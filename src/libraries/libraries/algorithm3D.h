//------------------------------------------------------------------------------
//-- Algorithm3D class
//------------------------------------------------------------------------------
//--
//--  Trains the algorithm for 3D recognition and matches the new information with the trained one.
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

#ifndef ALGORITHM_3D_H
#define ALGORITHM_3D_H

#include "dataparser.h"
#include <ocular/HandImage.h>
#include <algorithm>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/conversions.h>
#include <pcl/ros/conversions.h>
#include <pcl_conversions/pcl_conversions.h>

#include <pcl/point_cloud.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include <ros/console.h>

#include <sensor_msgs/PointCloud2.h>

//* Algorithm3D
/**
* Trains the algorithm for 3D recognition and matches the new information with the trained one.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date April 1st, 2014
*
*/
class Algorithm3D
{
public:

    /*!
    * \brief Public constructor
    */
    Algorithm3D();

    ~Algorithm3D();

    std::pair<int, float> match(const pcl::PCLPointCloud2ConstPtr &);

    void set_start_training(bool training);     /** Sets the value of the private boolean train*/

    void set_number_views (int);

    int add_descriptors(
        pcl::PCLPointCloud2 );

    int get_number_template();  /** Returns the number of the template being currently learned */

    void resize_vectors();

    void load_templates();

    void next_object();


private:

    DataParser dataparser;  /**DataParser object that will store and load the algorithms and templates information*/
    std::vector<cv::FlannBasedMatcher> algorithms2D;




    int flann_comparison (cv::Mat &, float);

    std::vector<std::vector< pcl::PCLPointCloud2 > >descriptors;    /** Vector that will store the descriptors dataset */


    int matched_object_id;  /** Number that represents the object being matched by the algorithm. **/

    float matched_object_ratio;  /** Number that represents the ratio obtained by the recognized object**/

    int object_number;

    int number_views;

    int object_id;

    bool matching;
};

#endif //ALGORITHM_3D_H
