#include "algorithm3D.h"

Algorithm3D::Algorithm3D()
{
    //    if (dataparser.getNumberAlgorithms()>1)
    //    {
    //        this->algorithms2D=dataparser.load_algorithms_2D();
    //    }

    //Initialize the matched_object_id to -1 until a match is found
    matched_object_id=-1;

    //Initialize object_number to 0 so if there are no previous templates, the first object has ID 0
    this->object_number=0;
}

Algorithm3D::~Algorithm3D()
{
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        while (descriptors[i].size()< this->number_views)
        {
            //            std::cerr<<"Object: "<<i<<"descriptor[i].size(): "<<descriptors[i].size()<<std::endl;
            descriptors[i].push_back(descriptors[i][0]);
        }
        dataparser.save_template(descriptors[i],i);
        std::cerr<<"template: "<<i<<" , number of views: "<<descriptors[i].size()<<std::endl;
    }
}

void Algorithm3D::set_number_views (int number_views)
{
    this->number_views=number_views;

    //    std::cerr<<"GET NUMBER OF TEMPLATES: "<<dataparser.getNumberTemplates()<<std::endl;
    //Load the previously stored templates if there are any
    if(dataparser.getNumberTemplates()>1)
    {
        dataparser.getTemplates(number_views,this->descriptors);
    }

    for (unsigned int i=0; i<descriptors.size(); i++)
        std::cerr<<"template: "<<i<<" , number of views: "<<descriptors[i].size()<<std::endl;


    this->set_new_object(true);

    this->alg3D.resize(descriptors.size());

    std::cerr<<"descriptors.size(): "<<descriptors.size()<<std::endl;
    std::cerr<<"Object number after setting number of views: "<<this->object_number<<std::endl;
}


void Algorithm3D::add_descriptors(const sensor_msgs::PointCloud2ConstPtr & msg, int number_view)
{
    //        ROS_ERROR("OBJECT NUMBER %d DESCRIPTORS SIZE %d", object_number, descriptors.size());
    //    std::cerr<<"adding descriptors in object_number: "<<object_number<<std::endl;
    descriptors[this->object_number].push_back(*msg);

}

void Algorithm3D ::set_new_object(bool new_object)
{
    this->new_object=new_object;

    if(this->new_object)
    {
        descriptors.push_back(std::vector<sensor_msgs::PointCloud2> ());
        alg3D.push_back(pcl::KdTreeFLANN <pcl::PFHSignature125> ());
        //        std::cerr<<"descriptors & alg2D size: "<<descriptors.size()<<" "<<alg2D.size()<<std::endl;
    }

    this->object_number=descriptors.size()-1;
}


int Algorithm3D::match3D(const sensor_msgs::PointCloud2ConstPtr & msg)
{
    //transform to pcl format
    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
    pcl::fromROSMsg(*msg, *msg_pcl);

    pcl::PointCloud<pcl::PFHSignature125>::Ptr cloud (new pcl::PointCloud<pcl::PFHSignature125> ());

    std::vector<int> ratio;
    ratio.resize(descriptors.size());

    //match3D
    for (unsigned int i=0; i<alg3D.size(); i++)
    {

        // Resize the output vector
        std::vector<int> correspondences_out;
        std::vector<float> correspondence_scores_out;

        correspondences_out.resize (descriptors[i].size ());
        correspondence_scores_out.resize (descriptors[i].size ());

        // Use a KdTree to search for the nearest matches in feature space
        alg3D[i].setInputCloud (msg_pcl);

        // Find the index of the best match for each keypoint, and store it in "correspondences_out"
        const int k = 1;
        std::vector<int> k_indices (k);
        std::vector<float> k_squared_distances (k);
        for (size_t j = 0; j < descriptors[i].size (); ++j)
        {
            pcl::fromROSMsg(descriptors[i][j], *cloud);
            //            alg3D[i].nearestKSearch (*cloud, j, k, k_indices, k_squared_distances);
            alg3D[i].radiusSearch(*cloud, j, k, k_indices, k_squared_distances);

            correspondences_out[j] = k_indices[0];
            correspondence_scores_out[j] = k_squared_distances[0];
        }
        ratio[i]=std::distance(correspondences_out.begin(), std::max_element(correspondences_out.begin(), correspondences_out.end()));
    }

    if (ratio.size()>0)
        this->matched_object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

    else
        this->matched_object_id=-1;

    return matched_object_id;
}

int Algorithm3D::get_number_template()
{
    return this->object_number;
}
