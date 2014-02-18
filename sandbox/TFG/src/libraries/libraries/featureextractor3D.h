#ifndef FEATURE_EXTRACTOR_3D_H
#define FEATURE_EXTRACTOR_3D_H


//#include "featureextractor.h"

//#include <pcl/recognition/linemod.h>
//#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
//#include <pcl/point_types.h>
//#include <pcl/recognition/line_rgbd.h>


//#include <math.h>
//#include <pcl/ros/conversions.h>
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/console/print.h>
//#include <pcl/console/parse.h>
//#include <pcl/console/time.h>

//#include <pcl/PointIndices.h>
//#include <pcl/ModelCoefficients.h>
//#include <pcl/sample_consensus/method_types.h>
//#include <pcl/sample_consensus/model_types.h>
//#include <pcl/segmentation/sac_segmentation.h>

//#include <pcl/recognition/linemod.h>
//#include <pcl/recognition/color_gradient_modality.h>
//#include <pcl/recognition/surface_normal_modality.h>
//#include <pcl/recognition/line_rgbd.h>

//#include <pcl/recognition/linemod/line_rgbd.h>


#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <pcl/features/pfh.h>

#include <pcl/features/normal_3d.h>

class FeatureExtractor3D
{
public:

    FeatureExtractor3D();

    void extract_features(const sensor_msgs::PointCloud2ConstPtr& msg);

};

#endif //FEATURE_EXTRACTOR_3D_H
