//------------------------------------------------------------------------------
//-- DataParser class
//------------------------------------------------------------------------------
//--
//--  Performs the saving and loading of the different templates and algorithms
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

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <opencv2/opencv.hpp>
#include <fstream>
#include <ros/ros.h>


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
    void save_template_2D(cv::Mat descriptors, int number_object, int number_view);


    std::vector<std::vector<cv::Mat> >  getTemplates (int);    /**Returns all the descriptors previously stored*/
    std::string get_path_to_pkg();

    int get_folder_number_of_items(std::string );
    int getNumberTemplates();

    int  getNumberAlgorithms();

private:
    std::vector <std::string> get_file_names (std::string );    /**Returns a vector of strings with the names of the files that are within the folder specified by the argument */


    std::string algorithms_2D_path; /**Path where the 2D algorithms are stored*/
    std::string algorithms_3D_path; /**Path where the 3D algorithms are stored*/
    std::string templates_path; /**Path where the templates are stored*/
    std::string temp_path;  /**Temporal files path*/

    std::string pkg_main_path;  /**Path of the ROS package*/

    void save_descriptor(cv::Mat &, std::string );




};

#endif // DATAPARSER_H
