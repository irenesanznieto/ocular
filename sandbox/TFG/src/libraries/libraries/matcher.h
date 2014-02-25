#ifndef MATCHER_H
#define MATCHER_H

#include "dataparser.h"

class Matcher
{
public:
    Matcher();
    void match();
    std::vector <cv::DMatch> flann_comparison (cv::Mat  &, 	cv::Mat  &, float &, float);

private:
    void match2D();

};
#endif //MATCHER_H
