#include "featureextractor3D.h"

FeatureExtractor3D::FeatureExtractor3D()
{
    pc_sub=nh.subscribe<sensor_msgs::PointCloud2>("input", 1, &FeatureExtractor3D::extract_features , this);
}


void FeatureExtractor3D:: extract_features(const sensor_msgs::PointCloud2ConstPtr & msg)
{
//    pcl::LineRGBD<pcl::PointXYZRGBA> line_rgbd;
}
