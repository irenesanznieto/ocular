#ifndef FEATURE_EXTRACTOR_3D_H
#define FEATURE_EXTRACTOR_3D_H

#include "featureextractor.h"
#include "roisegmenter3D.h"

class FeatureExtractor3D: public FeatureExtractor
{
	public: 
	
		void extract_features(); 

	private: 
	
		RoiSegmenter3D roi_seg; 
};

#endif //FEATURE_EXTRACTOR_3D_H
