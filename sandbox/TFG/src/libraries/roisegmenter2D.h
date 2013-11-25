#ifndef ROI_SEGMENTER_2D_H
#define ROI_SEGMENTER_2D_H

#include "roisegmenter.h"
#include <opencv2/opencv.hpp>


class RoiSegmenter2D: public RoiSegmenter
{
	public: 
		cv::Mat segment(); 

};
#endif //ROI_SEGMENTER_2D_H
