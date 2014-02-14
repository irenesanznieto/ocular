#include "featureextractor3D.h"

FeatureExtractor3D::FeatureExtractor3D()
{
    pc_sub=nh.subscribe<sensor_msgs::PointCloud2>("input", 1, &FeatureExtractor3D::extract_features , this);
}


void FeatureExtractor3D:: extract_features(const sensor_msgs::PointCloud2ConstPtr & msg)
{
    // LINE-MOD instance using color gradients and depth normals with default
    // (VGA-suitable) parameters and two pyramid levels.
    cv::Ptr<cv::linemod::Detector> detector = cv::linemod::getDefaultLINEMOD();

    // For each (color, depth) view with object in mask, compute a template
    std::string class_id = "example"; // One object class in this example
//    for (...)
//    {
      // sources contains one cv::Mat source image per modality, in order.
      // Default LINE-MOD uses modalities (ColorGradient, DepthNormal).
      std::vector<cv::Mat> sources;
      cv::Mat color, depth;

      sources.push_back(color);
      sources.push_back(depth);

      // Train a new set of templates
      int template_id = detector->addTemplate(sources, class_id, cv::Mat());
//    }



}


// STORE THE TEMPLATES!!

// Can then use for detection or write to disk
//    cv::FileStorage fs("objects.yml.gz", cv::FileStorage::WRITE);
//    detector->write(fs);
