#include "matcher.h"

Matcher::Matcher()
{
    this->algorithms2D=dataparser.load_algorithms_2D();
}

int Matcher :: match2D(const TFG::HandImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;

    //resulting object id
    int object_id=0;

    for (unsigned int i=0; i<msg->image.size(); i++)
    {
        //transform from ROS msg to OpenCV msg
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        //threshold used in the flann_comparison
        float  threshold=300;

        //compare FLANN
        object_id=this->flann_comparison(cv_ptr->image, threshold);
    }

    return object_id;
}

int Matcher:: flann_comparison (cv::Mat  &desc1,float threshold)
{
    //vector that will store the ratios of similarity between the new image and the templates
    std::vector< float> ratio;
    //resize the vector
    ratio.resize(algorithms2D.size());

    //vector to store the distances between descriptors
    std::vector<std::vector< cv::DMatch > >matches;
    //resize the vector
    matches.resize(algorithms2D.size());

    //Store good matches, using the threshold ratio
    std::vector<std::vector< cv::DMatch > >good_matches;
    good_matches.resize(algorithms2D.size());

    //for each algorithm, match the new descriptors with the algorithm's information
    for (unsigned int object_number=0; object_number<algorithms2D.size(); object_number++)
    {
        desc1.convertTo(desc1, CV_32F);

        //match each algorithm with the new cv::Mat and output the result in the matches vector
        algorithms2D[object_number].match( desc1, matches[object_number]);

        //decide which are the good matches (i.e. matches whose distance is lower than the threshold) of the above matches
        for( int i = 0; i < desc1.rows; i++ )
        {
            if( matches[object_number][i].distance < threshold )
                good_matches[object_number].push_back( matches[object_number][i]);
        }
        //cout <<good_matches.size()<<endl<<matches.size()<<endl;

        //The ratio is defined as the number of good_matches  over the number of total matches
        //This ratio is defined for each algorithm. Since each algorithm will be used for each object, this will be the similarity with this object
        ratio[object_number]=(float)(good_matches[object_number].size())/(float)(matches[object_number].size());
    }

    //Obtain the object ID as the vector position with the maximum of the ratios
    int object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

    return object_id;
}

void Matcher::match3D(const sensor_msgs::PointCloud2ConstPtr & msg)
{
    //transform to pcl format
    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
    pcl::fromROSMsg(*msg, *msg_pcl);

    pcl::PointCloud<pcl::PFHSignature125>::Ptr dataset_descriptors (new pcl::PointCloud<pcl::PFHSignature125> ());

    //match3D

    // Resize the output vector
    std::vector<int> correspondences_out;
    std::vector<float> correspondence_scores_out;

    correspondences_out.resize (dataset_descriptors->size ());
    correspondence_scores_out.resize (dataset_descriptors->size ());

    // Use a KdTree to search for the nearest matches in feature space
    pcl::KdTreeFLANN<pcl::PFHSignature125> descriptor_kdtree;
    descriptor_kdtree.setInputCloud (msg_pcl);

    // Find the index of the best match for each keypoint, and store it in "correspondences_out"
    const int k = 1;
    std::vector<int> k_indices (k);
    std::vector<float> k_squared_distances (k);
    for (size_t i = 0; i < dataset_descriptors->size (); ++i)
    {
        descriptor_kdtree.nearestKSearch (*dataset_descriptors, i, k, k_indices, k_squared_distances);
        correspondences_out[i] = k_indices[0];
        correspondence_scores_out[i] = k_squared_distances[0];
    }
}

///////////////////////////TODO:
//weights between the two

//publish resulting name!






