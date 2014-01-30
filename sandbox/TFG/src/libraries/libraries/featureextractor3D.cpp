#include "featureextractor3D.h"

FeatureExtractor3D::FeatureExtractor3D()
{
    pc_sub=nh.subscribe<sensor_msgs::PointCloud2>("input", 1, &FeatureExtractor3D::extract_features , this);
}


void FeatureExtractor3D:: extract_features(const sensor_msgs::PointCloud2ConstPtr & msg)
{
//    pcl::PointCloud<pcl::PointXYZRGBA> ::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA> ());
//    pcl::fromROSMsg (*msg, *cloud);
//    pcl::LineRGBD<pcl::PointXYZRGBA> line_rgbd;
//    line_rgbd.setInputCloud(cloud);
//    line_rgbd.setInputColors(cloud);

////    setup mask of the desired object to train
//    pcl::MaskMap mask_map (width, height);
////    fill mask

//    line_rgbd.createAndAddTemplate(cloud, object_id, mask_map, mask_map,region );

}
