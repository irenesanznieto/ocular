#ifndef FEATURE_EXTRACTOR_3D_H
#define FEATURE_EXTRACTOR_3D_H


//#include "featureextractor.h"

//#include <pcl/recognition/linemod.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
//#include <pcl/point_types.h>
#include <pcl/recognition/linemod/line_rgbd.h>



//#include <TFG/

class FeatureExtractor3D/*: public FeatureExtractor*/
{
public:

    FeatureExtractor3D();
    ros::Subscriber pc_sub;
    //        ros::Publisher
    ros::NodeHandle nh;
    void extract_features(const sensor_msgs::PointCloud2ConstPtr& msg);

};

#endif //FEATURE_EXTRACTOR_3D_H
