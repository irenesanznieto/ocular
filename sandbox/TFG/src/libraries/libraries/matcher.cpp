#include "matcher.h"

Matcher::Matcher()
{
    this->training=false;
    this->algorithms2D= dataparser.load_algorithms_2D();


}

int Matcher :: match2D(const TFG::HandImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    int object_id=0;

    if (this->training==false)
    {

        //match2D
        for (unsigned int i=0; i<msg->image.size(); i++)
        {

            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
            }

            float  threshold=300;
            object_id=this->flann_comparison(cv_ptr->image, threshold);
        }
        return object_id;
    }
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



int Matcher:: flann_comparison (cv::Mat  &desc1,float threshold)
{
    std::vector< float> ratio;
    ratio.resize(algorithms2D.size());

    std::vector<std::vector< cv::DMatch > >matches;
    matches.resize(algorithms2D.size());

    //Store good matches, using the threshold ratio
    std::vector<std::vector< cv::DMatch > >good_matches;
    good_matches.resize(algorithms2D.size());

    for (unsigned int object_number=0; object_number<algorithms2D.size(); object_number++)
    {

        desc1.convertTo(desc1, CV_32F);

        algorithms2D[object_number].match( desc1, matches[object_number]);



        for( int i = 0; i < desc1.rows; i++ )
        {
            if( matches[object_number][i].distance < threshold )
                good_matches[object_number].push_back( matches[object_number][i]);
        }


        //cout <<good_matches.size()<<endl<<matches.size()<<endl;

        //This ratio will help define the correct match for each photo
        ratio[object_number]=(float)(good_matches[object_number].size())/(float)(matches[object_number].size());
    }


    int object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

    return object_id;
}

void Matcher::set_start_training(bool training)
{
    this->training=training;
}
