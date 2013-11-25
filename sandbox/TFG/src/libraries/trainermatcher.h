#ifndef TRAINER_MATCHER_H
#define TRAINER_MATCHER_H

#include "dataparser.h"
#include "featureextractor2D.h"
#include "featureextractor3D.h"

//#include <pcl/recognition/line_rgbd.h>

class TrainerMatcher
{
	public:
		void extract_features();
		void save();
		void load();
		
	protected: 
	
		DataParser dataparser; 
		
		//2D: 
		cv::ORB orb; 
		FeatureExtractor2D fe2D; 




		//3D: 
		FeatureExtractor3D fe3D; 
		//pcl::LineRGBD <pcl::PointXYZRGBA> line_rgbd; 
};

#endif //TRAINER_MATCHER_H
