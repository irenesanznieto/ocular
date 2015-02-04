#include "featureextractor3D.h"

FeatureExtractor3D::FeatureExtractor3D()
{
}



pcl::PCLPointCloud2 FeatureExtractor3D::extract_features(std::string name,
                                                         const pcl::PCLPointCloud2ConstPtr & msg)
{
    if (name=="pfh")
        return extract_features_pfh(msg);
    else if (name=="fpfh")
        return extract_features_fpfh(msg);
    else if(name=="vhf")
        return extract_features_vhf(msg);
    else
        std::cerr<<"[FeatureExtractor3D]    No such descriptor available"<<std::endl<<std::flush;


}

pcl::PCLPointCloud2 FeatureExtractor3D::extract_features_vhf(
        const pcl::PCLPointCloud2ConstPtr & msg_in)
{

    pcl::PCLPointCloud2Ptr msg (new pcl::PCLPointCloud2 ());
    //Downsample point cloud:
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud (msg_in);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*msg);

    // Cloud for storing the object.
    pcl::PointCloud<pcl::PointXYZ>::Ptr object(new pcl::PointCloud<pcl::PointXYZ>);
    // Object for storing the normals.
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    // Object for storing the VFH descriptor.
    pcl::PointCloud<pcl::VFHSignature308>::Ptr descriptor(new pcl::PointCloud<pcl::VFHSignature308>);

// //////////////////////////////////////////////////////////////////////////////////////////////
// // VGonPa Modified this. Please uncomment first line and remove the rest to undo changes    //
// //////////////////////////////////////////////////////////////////////////////////////////////
    pcl::fromROSMsg(*msg, *object);
// //////////////////////////////////////////////////////////////////////////////////////////////
//    object = pcl_conversions::toPCL(*msg);
//    pcl_conversions::toPCL(*msg, *object);

// Function signatures
//    void pcl::fromROSMsg        (const sensor_msgs::PointCloud2 & msg, pcl::PointCloud<PointT> & cloud)
//    void pcl_conversions::toPCL	(const sensor_msgs::PointCloud2 & pc2, pcl::PCLPointCloud2 & pcl_pc2)

// //////////////////////////////////////////////////////////////////////////////////////////////

    // Estimate the normals.
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud(object);
    normalEstimation.setRadiusSearch(0.03);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
    normalEstimation.setSearchMethod(kdtree);
    normalEstimation.compute(*normals);


    // VFH estimation object.
    pcl::VFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> vfh;
    vfh.setInputCloud(object);
    vfh.setInputNormals(normals);
    vfh.setSearchMethod(kdtree);
    // Optionally, we can normalize the bins of the resulting histogram,
    // using the total number of points.
    vfh.setNormalizeBins(true);
    // Also, we can normalize the SDC with the maximum size found between
    // the centroid and any of the cluster's points.
    vfh.setNormalizeDistance(false);


    // Compute the features
    vfh.compute(*descriptor);


        pcl::PCLPointCloud2  result;
    pcl::toROSMsg(*descriptor, result );

    return result;
}


        pcl::PCLPointCloud2   FeatureExtractor3D:: extract_features_fpfh(const
        pcl::PCLPointCloud2ConstPtr & msg_in)
{

        pcl::PCLPointCloud2Ptr msg (new
        pcl::PCLPointCloud2 ());

//    //std::cerr << "Original input msg size: "<<msg_in->data.size()<<std::endl;
    //Downsample point cloud:
    pcl::VoxelGrid<
        pcl::PCLPointCloud2 > sor;
    sor.setInputCloud (msg_in);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*msg);

//    //std::cerr << "Downsampled input msg size: "<<msg->data.size()<<std::endl;

    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());

    pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_msg ( new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*msg, *pcl_msg);

   //Normal:

        //std::cerr<<"NORMAL COMPUTATION"<<std::endl;

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> norm_est;

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());

    // Use a FLANN-based KdTree to perform neighborhood searches
    norm_est.setSearchMethod (tree);

    // Specify the size of the local neighborhood to use when computing the surface normals
    norm_est.setRadiusSearch (0.03);

    // Set the input points
    norm_est.setInputCloud (pcl_msg);

    // Estimate the surface normals and store the result in "normals_out"
    norm_est.compute (*normals);

//    std::cerr<<"NORMAL COMPUTATION"<<std::endl;

    // Create the FPFH estimation class, and pass the input dataset+normals to it
    pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
    fpfh.setInputCloud (pcl_msg);
    fpfh.setInputNormals (normals);
    // alternatively, if cloud is of tpe PointNormal, do fpfh.setInputNormals (cloud);

    // Create an empty kdtree representation, and pass it to the FPFH estimation object.
    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZ>);

    fpfh.setSearchMethod (tree2);
    // Output datasets
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs (new pcl::PointCloud<pcl::FPFHSignature33> ());

    // Use all neighbors in a sphere of radius 5cm
    // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
    fpfh.setRadiusSearch (0.05);

    // Compute the features
    fpfh.compute (*fpfhs);
    //std::cerr<<"FEATURE COMPUTATION FNISHED"<<std::endl;



        pcl::PCLPointCloud2  result;
    pcl::toROSMsg(*fpfhs, result );

    return result;
}


        pcl::PCLPointCloud2   FeatureExtractor3D:: extract_features_pfh(const
        pcl::PCLPointCloud2ConstPtr & msg_in)
{


        pcl::PCLPointCloud2Ptr msg (new pcl::PCLPointCloud2 ());

    //Downsample point cloud:
    pcl::VoxelGrid<
        pcl::PCLPointCloud2 > sor;
    sor.setInputCloud (msg_in);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*msg);

    pcl::PointCloud<pcl::PointXYZ>::Ptr msg_pcl (new pcl::PointCloud<pcl::PointXYZ> ());

    pcl::fromROSMsg(*msg, *msg_pcl);


    //PFH:


//    // ------------> KEYPOINTS

//    //
//    //  ISS3D parameters
//    //
//    double iss_salient_radius_;
//    double iss_non_max_radius_;
//    double iss_gamma_21_ (0.975);
//    double iss_gamma_32_ (0.975);
//    double iss_min_neighbors_ (5);
//    int iss_threads_ (4);

//    pcl::PointCloud<pcl::PointXYZ>::Ptr model (new pcl::PointCloud<pcl::PointXYZ> ());
//    pcl::PointCloud<pcl::PointXYZ>::Ptr model_keypoints (new pcl::PointCloud<pcl::PointXYZ> ());
//    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());

//    // Fill in the model cloud

//    pcl::fromROSMsg(*msg_in, *model);



//    double model_resolution=0.2;

//    // Compute model_resolution

//    iss_salient_radius_ = 6 * model_resolution;
//    iss_non_max_radius_ = 4 * model_resolution;

//    //
//    // Compute keypoints
//    //
//    pcl::ISSKeypoint3D<pcl::PointXYZ, pcl::PointXYZ> iss_detector;

//    iss_detector.setSearchMethod (tree);
//    iss_detector.setSalientRadius (iss_salient_radius_);
//    iss_detector.setNonMaxRadius (iss_non_max_radius_);
//    iss_detector.setThreshold21 (iss_gamma_21_);
//    iss_detector.setThreshold32 (iss_gamma_32_);
//    iss_detector.setMinNeighbors (iss_min_neighbors_);
//    iss_detector.setNumberOfThreads (iss_threads_);
//    iss_detector.setInputCloud (model);
//    iss_detector.compute (*model_keypoints);


//// ------------> KEYPOINTS







    pcl::PointCloud<pcl::Normal>::Ptr normals_out (new pcl::PointCloud<pcl::Normal> ());
    //Normal:

        //std::cerr<<"NORMAL COMPUTATION"<<std::endl;

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> norm_est;

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree3 (new pcl::search::KdTree<pcl::PointXYZ> ());

    // Use a FLANN-based KdTree to perform neighborhood searches
    norm_est.setSearchMethod (tree3);

    // Specify the size of the local neighborhood to use when computing the surface normals
    norm_est.setRadiusSearch (0.03);

    // Set the input points
    norm_est.setInputCloud (msg_pcl);

    // Estimate the surface normals and store the result in "normals_out"
    norm_est.compute (*normals_out);

    //std::cerr<<"NORMAL ESTIMATION DONE"<<std::endl;

    // Descriptors:
    // Create a PFHEstimation object
    pcl::PFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::PFHSignature125> pfh_est;
    //std::cerr<<"PFH ESTIMATION"<<std::endl;

    const pcl::search::KdTree<pcl::PointXYZ>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZ> ());

    // Set it to use a FLANN-based KdTree to perform its neighborhood searches
    pfh_est.setSearchMethod (tree2);

    // Specify the radius of the PFH feature
    pfh_est.setRadiusSearch (0.03);

      pfh_est.setSearchSurface (msg_pcl);
    // Set the input points and surface normals
    pfh_est.setInputCloud (msg_pcl);

    pfh_est.setInputNormals (normals_out);


    // Compute the features
    pcl::PointCloud<pcl::PFHSignature125>::Ptr descriptors_out(new pcl::PointCloud<pcl::PFHSignature125> ());
    pfh_est.compute (*descriptors_out);

    //std::cerr<<"PFH ESTIMATION DONE"<<std::endl;


        pcl::PCLPointCloud2  result;
    pcl::toROSMsg(*descriptors_out, result );

    return result;






    ////    //std::cerr<<"Input message size: "<<msg->data.size()<<std::endl<<"After fromROSMsg cloud size: "<<pcl_msg->size()<<std::endl;

    //    // Create the normal estimation class, and pass the input dataset to it
    //    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    //    ne.setInputCloud (pcl_msg);

    //    // Create an empty kdtree representation, and pass it to the normal estimation object.
    //    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    //    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
    //    ne.setSearchMethod (tree);

    //    // Output datasets
    //    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());


    //    // Create the PFH estimation class, and pass the input dataset+normals to it
    //    pcl::PFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::PFHSignature125> pfh;
    //    pfh.setInputCloud (pcl_msg);

    //    // Use all neighbors in a sphere of radius 3cm
    //    ne.setRadiusSearch (0.03);

    //    // Compute the features
    //    ne.compute (*normals);


    //    //std::cerr<<"3D ----> Normals computed"<<std::endl;

    //    pfh.setInputNormals (normals);
    //    // alternatively, if cloud is of tpe PointNormal, do pfh.setInputNormals (cloud);

    //    // Create an empty kdtree representation, and pass it to the PFH estimation object.
    //    // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
    //        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZ> ());
    //    //pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr tree (new pcl::KdTreeFLANN<pcl::PointXYZ> ()); -- older call for PCL 1.5-
    //    pfh.setSearchMethod (tree2);

    //    // Output datasets
    //    pcl::PointCloud<pcl::PFHSignature125>::Ptr pfhs (new pcl::PointCloud<pcl::PFHSignature125> ());
    ////    pcl::PointCloud<pcl::PFHSignature125> pfhs;

    //    // Use all neighbors in a sphere of radius 5cm
    //    // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
    //    pfh.setRadiusSearch (0.05);

    //    //std::cerr<<"3D ----> Parameters setted"<<std::endl;

    //    // Compute the features
    //    pfh.compute (*pfhs);

    //    //std::cerr<<"3D ----> Features computed"<<std::endl;

    //
    //    pcl::PCLPointCloud2  result;
    //    pcl::toROSMsg(*pfhs, result );

    //    return result;

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





