#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <opencv2/opencv.hpp>
#include <fstream>

class DataParser
{
public:
    DataParser();


    cv::Mat load_descriptor (std::string );/** */
    void load_algorithms_2D(std::string);/** */
    void save_algorithm_2D();/** */
    void save_template_2D();/** */
    std::vector<std::vector<cv::Mat> >  getTemplates ();/** */



private:
    std::vector <std::string> get_file_names (std::string );    /**Returns a vector of strings with the names of the files that are within the folder specified by the argument */

    std::string algorithms_2D_path; /**Path where the 2D algorithms are stored*/
    std::string algorithms_3D_path; /**Path where the 3D algorithms are stored*/
    std::string templates_path; /**Path where the templates are stored*/
    std::string temp_path;  /**Temporal files path*/


};

#endif // DATAPARSER_H
