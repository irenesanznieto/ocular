//------------------------------------------------------------------------------
//-- DataParser class
//------------------------------------------------------------------------------
//--
//--  Performs the saving and loading of the different templates and algorithms
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

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <opencv2/opencv.hpp>
#include <fstream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ros/conversions.h>

//trying:
#include <stdio.h>  /* defines FILENAME_MAX */
#include <unistd.h>


//* DataParser
/**
* Performs the saving and loading of the different templates and algorithms.
* \author Irene Sanz Nieto ( https://github.com/irenesanznieto )
* \date Feb 25th, 2014
*
*/
class DataParser
{
public:

    /*!
    * \brief Public constructor
    */
    DataParser();


    cv::Mat load_descriptor (std::string ); /**Loads the descriptors specified by the input string*/
    std::vector<cv::FlannBasedMatcher> load_algorithms_2D();    /**Loads the FlannBasedMatcher algorithms information previously stored*/
    void save_algorithm_2D(cv::FlannBasedMatcher & , int ); /**Stores the FlannBasedMatcher algorithm information to the algorithms folder*/
    void save_template_2D(std::vector<cv::Mat> & , int ); /**Saves a new 2D template in the predefined path */
    void save_template(cv::Mat descriptors, int number_object, int number_view);


    void save_template(std::vector<
        pcl::PCLPointCloud2 > & , int ); /**Saves a new 2D template in the predefined path */


    void getTemplates (int, std::vector<std::vector<cv::Mat> > &  );    /**Returns all the descriptors previously stored*/
    void getTemplates (int, std::vector<std::vector<
        pcl::PCLPointCloud2 > > &  );    /**Returns all the descriptors previously stored*/

    std::string get_path_to_pkg();

    int get_folder_number_of_items(std::string );
    int getNumberTemplates(std::string);

    int  getNumberAlgorithms();

    //make private!!!
    std::vector <std::string> get_file_names (std::string );    /**Returns a vector of strings with the names of the files that are within the folder specified by the argument */


private:


        pcl::PCLPointCloud2  load_descriptor3D(std::string filename);

    void save_descriptor(
        pcl::PCLPointCloud2  &descriptors, std::string filename);


    std::string algorithms_2D_path; /**Path where the 2D algorithms are stored*/
    std::string algorithms_3D_path; /**Path where the 3D algorithms are stored*/
    std::string templates_path_2D; /**Path where the templates 2D are stored*/
    std::string templates_path_3D; /**Path where the templates 3D are stored*/

    std::string temp_path;  /**Temporal files path*/

    std::string pkg_main_path;  /**Path of the ROS package*/

    void save_descriptor(cv::Mat &, std::string );

    std::string getexepath();


};

#endif // DATAPARSER_H
