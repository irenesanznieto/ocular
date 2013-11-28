#ifndef ROISEGMENTER2D_H
#define ROISEGMENTER2D_H

#include "roisegmenter.h"

class RoiSegmenter2D: public RoiSegmenter
{
public:
    RoiSegmenter2D();
    cv::Mat segment();

};

#endif // ROISEGMENTER2D_H
