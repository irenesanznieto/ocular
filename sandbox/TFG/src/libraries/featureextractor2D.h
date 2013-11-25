#ifndef FEATURE_EXTRACTOR_2D_H
#define FEATURE_EXTRACTOR_2D_H

#include "featureextractor.h"
#include "roisegmenter2D.h"

#include <opencv2/opencv.hpp>
#include <iostream>

class FeatureExtractor2D: public FeatureExtractor
{
	public: 
	
		std::pair <cv::Mat, std::vector<cv::KeyPoint> >  extract_features(); 

};

#endif //FEATURE_EXTRACTOR_2D_H
