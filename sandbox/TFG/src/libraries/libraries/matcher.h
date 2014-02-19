#ifndef MATCHER_H
#define MATCHER_H

#include <opencv2/opencv.hpp>
//#include <vector>

class Matcher
{
public:
    void match();
    std::vector <cv::DMatch> flann_comparison (cv::Mat  &, 	cv::Mat  &, float &, float);

private:
    void match2D();

};
#endif //MATCHER_H
