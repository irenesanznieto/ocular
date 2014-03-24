//#include "matcher.h"

//Matcher::Matcher()
//{
//    if (dataparser.getNumberAlgorithms()>1)
//    {
//        this->algorithms2D=dataparser.load_algorithms_2D();
//    }
//}


//void Matcher::match3D(const sensor_msgs::PointCloud2ConstPtr & msg)
//{
//    //transform to pcl format
//    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
//    pcl::fromROSMsg(*msg, *msg_pcl);

//    pcl::PointCloud<pcl::PFHSignature125>::Ptr dataset_descriptors (new pcl::PointCloud<pcl::PFHSignature125> ());

//    //match3D

//    // Resize the output vector
//    std::vector<int> correspondences_out;
//    std::vector<float> correspondence_scores_out;

//    correspondences_out.resize (dataset_descriptors->size ());
//    correspondence_scores_out.resize (dataset_descriptors->size ());

//    // Use a KdTree to search for the nearest matches in feature space
//    pcl::KdTreeFLANN<pcl::PFHSignature125> descriptor_kdtree;
//    descriptor_kdtree.setInputCloud (msg_pcl);

//    // Find the index of the best match for each keypoint, and store it in "correspondences_out"
//    const int k = 1;
//    std::vector<int> k_indices (k);
//    std::vector<float> k_squared_distances (k);
//    for (size_t i = 0; i < dataset_descriptors->size (); ++i)
//    {
//        descriptor_kdtree.nearestKSearch (*dataset_descriptors, i, k, k_indices, k_squared_distances);
//        correspondences_out[i] = k_indices[0];
//        correspondence_scores_out[i] = k_squared_distances[0];
//    }
//}

/////////////////////////////TODO:
////weights between the two

////publish resulting name!






