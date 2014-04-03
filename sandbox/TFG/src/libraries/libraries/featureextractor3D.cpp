#include "featureextractor3D.h"

FeatureExtractor3D::FeatureExtractor3D()
{
}


sensor_msgs::PointCloud2  FeatureExtractor3D:: extract_features(const sensor_msgs::PointCloud2ConstPtr & msg)
{
// COMPUTE PFH ONLY AT KEYPOINTS??  /Desktop/PFH Demo

    //PFH:

    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_msg ( new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *pcl_msg);


    // Create the PFH estimation class, and pass the input dataset+normals to it
    pcl::PFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::PFHSignature125> pfh;


    pfh.setInputCloud (pcl_msg);


    // Create the normal estimation class, and pass the input dataset to it


    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setInputCloud (pcl_msg);

    // Create an empty kdtree representation, and pass it to the normal estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
    ne.setSearchMethod (tree);

    // Output datasets
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());

    // Use all neighbors in a sphere of radius 3cm
    ne.setRadiusSearch (0.03);

    // Compute the features
    ne.compute (*normals);


    pfh.setInputNormals (normals);
    // alternatively, if cloud is of tpe PointNormal, do pfh.setInputNormals (cloud);

    // Create an empty kdtree representation, and pass it to the PFH estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    //    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
    //pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr tree (new pcl::KdTreeFLANN<pcl::PointXYZ> ()); -- older call for PCL 1.5-
    pfh.setSearchMethod (tree);

    // Output datasets
    pcl::PointCloud<pcl::PFHSignature125>::Ptr pfhs (new pcl::PointCloud<pcl::PFHSignature125> ());
//    pcl::PointCloud<pcl::PFHSignature125> pfhs;

    // Use all neighbors in a sphere of radius 5cm
    // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
    pfh.setRadiusSearch (0.05);

    // Compute the features
    pfh.compute (*pfhs);

    sensor_msgs::PointCloud2 result;
    pcl::toROSMsg(*pfhs, result );

    return result;

}






//  LINEMOD:
//    using namespace pcl;
//    using namespace pcl::io;
//    using namespace pcl::console;

//    typedef pcl::PointCloud<pcl::PointXYZRGBA> PointCloudXYZRGBA;


//    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr pcl_msg ( new pcl::PointCloud<pcl::PointXYZRGBA>);
//    pcl::fromROSMsg(*msg, *pcl_msg);

//    pcl::LINEMOD linemod;


//    pcl::ColorGradientModality<pcl::PointXYZRGBA> color_grad_mod;
//     color_grad_mod.setInputCloud (pcl_msg);
//     color_grad_mod.processInputData ();

//     pcl::SurfaceNormalModality<pcl::PointXYZRGBA> surface_norm_mod;
//     surface_norm_mod.setInputCloud (pcl_msg);
//     surface_norm_mod.processInputData ();

//     std::vector<pcl::QuantizableModality*> modalities (2);
//     modalities[0] = &color_grad_mod;
//     modalities[1] = &surface_norm_mod;

//     std::vector<bool> foreground_mask (pcl_msg->size (), false);


//     size_t min_x (pcl_msg->width), min_y (pcl_msg->height), max_x (0), max_y (0);
//     pcl::MaskMap mask_map (pcl_msg->width, pcl_msg->height);
//     for (size_t j = 0; j < pcl_msg->height; ++j)
//     {
//       for (size_t i = 0; i < pcl_msg->width; ++i)
//       {
//         mask_map (i,j) = foreground_mask[j*pcl_msg->width+i];
//         if (foreground_mask[j*pcl_msg->width+i])
//         {
//           min_x = std::min (min_x, i);
//           max_x = std::max (max_x, i);
//           min_y = std::min (min_y, j);
//           max_y = std::max (max_y, j);
//         }
//       }
//     }

//     std::vector<pcl::MaskMap*> masks (2);
//     masks[0] = &mask_map;
//     masks[1] = &mask_map;

//     pcl::RegionXY region;
//     region.x = static_cast<int> (min_x);
//     region.y = static_cast<int> (min_y);
//     region.width = static_cast<int> (max_x - min_x + 1);
//     region.height = static_cast<int> (max_y - min_y + 1);

////     printf ("%d %d %d %d\n", region.x, region.y, region.width, region.height);

////     linemod.createAndAddTemplate()
//     linemod.createAndAddTemplate (modalities, masks, region);





