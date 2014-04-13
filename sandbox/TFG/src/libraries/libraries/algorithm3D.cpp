#include "algorithm3D.h"

Algorithm3D::Algorithm3D()
{
    //Initialize the matched_object_id to -1 until a match is found
    matched_object_id=-1;

    //Initialize object_number to 0 so if there are no previous templates, the first object has ID 0
    this->object_number=0;

    descriptors.resize(1);
    alg3D.resize(1);
}

Algorithm3D::~Algorithm3D()
{
    std::cerr<<std::endl<<"[LearnerRecognizer -- Algorithm3D]   SAVING TEMPLATES 3D: "<<std::endl<<std::flush;
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        if(descriptors[i].size()<this->number_views)
        {
            descriptors.erase(descriptors.begin()+i-1);
        }
        else
        {
            dataparser.save_template(descriptors[i],i);
            std::cerr<<"    template: "<<i<<" , number of views: "<<descriptors[i].size()<<std::endl<<std::flush;
        }
    }
    std::cerr<<std::endl<<std::flush;
}


void Algorithm3D::load_templates()
{
    if(dataparser.getNumberTemplates("3D")>1)
    {
        dataparser.getTemplates(number_views,this->descriptors);
        this->next_object();
        this->alg3D.resize(descriptors.size());

        std::cerr<<std::endl<<"[LearnerRecognizer -- Algorithm3D]   LOADED "<<descriptors.size()-1<< " TEMPLATES 3D "<<std::endl<<std::endl<<std::flush;
    }
}

void Algorithm3D::next_object()
{
    descriptors.push_back(std::vector<sensor_msgs::PointCloud2> ());
    alg3D.push_back(pcl::KdTreeFLANN <pcl::PFHSignature125> ());
    this->object_number=descriptors.size()-1;

}

void Algorithm3D::set_number_views (int number_views)
{
    this->number_views=number_views;
}


int Algorithm3D::add_descriptors(sensor_msgs::PointCloud2 msg)
{
    //    std::cerr<<"add descriptors 3D: data.empty?: "<<msg.data.empty()<<" object_number: "<<this->object_number<<" descriptors.size: "<<descriptors.size()<<std::endl<<std::flush;

    if(msg.data.empty())
        return -1;
    else if (!msg.data.empty())
    {
        descriptors[this->object_number].push_back(msg);
        return 0;
    }
}

void Algorithm3D ::set_new_object(bool new_object)
{
    this->new_object=new_object;
}


int Algorithm3D::match(const sensor_msgs::PointCloud2ConstPtr & msg)
{
//            std::cerr<<"match3D "<<std::endl<<std::flush;

    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
    pcl::fromROSMsg(*msg, *msg_pcl);
//    std::cerr<<"match3D "<<std::endl<<std::flush;


        pcl::PointCloud<pcl::PFHSignature125>::Ptr cloud (new pcl::PointCloud<pcl::PFHSignature125> ());

//        std::cerr<<"match3D "<<std::endl<<std::flush;

    // Use a KdTree to search for the nearest matches in feature space
    pcl::KdTreeFLANN <pcl::PFHSignature125> descriptor_kdtree;
    descriptor_kdtree.setInputCloud (msg_pcl);

    std::vector<int> correspondences;

//    std::cerr<<"match3D "<<std::endl<<std::flush;

    // Find the index of the best match for each keypoint, and store it in "correspondences_out"
    const int k = 1;

    for(int obj_numb=0; obj_numb<descriptors.size()-1; obj_numb++)
    {

        std::vector<int> k_indices (k);
        std::vector<float> k_squared_distances (k);
//        std::cerr<<" ------match3D"<<std::endl<<std::flush;


        for (int i = 0; i < static_cast<int> (descriptors[obj_numb].size()); ++i)
        {
            pcl::fromROSMsg(descriptors[obj_numb][i], *cloud);

//            std::cerr<<" ------match3D------"<<std::endl<<std::flush;

            descriptor_kdtree.nearestKSearch(*cloud, i, k, k_indices, k_squared_distances);

//            std::cerr<<" ------match3D------"<<std::endl<<std::flush;
            correspondences.push_back(k_indices[0]);
        }
//        std::cerr<<"match3D "<<std::endl<<std::flush;

    }
}

//    std::cerr<<"match3D"<<std::endl<<std::flush;

//    //transform to pcl format
//    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
//    pcl::fromROSMsg(*msg, *msg_pcl);


//    pcl::PointCloud<pcl::PFHSignature125>::Ptr cloud (new pcl::PointCloud<pcl::PFHSignature125> ());

//    std::vector<int> ratio;
//    ratio.resize(descriptors.size()-1);


//    //segmentation fault here :S xD:

//    //match3D
//    for (unsigned int i=0; i<alg3D.size()-1; i++)
//    {


//        // Resize the output vector
//        std::vector<int> correspondences_out;
//        std::vector<float> correspondence_scores_out;


//        correspondences_out.resize (descriptors[i].size());
//        correspondence_scores_out.resize (descriptors[i].size());

//        std::cerr<<"correspondences_out.size(): "<<correspondences_out.size()<<std::endl<<std::flush;

//        // Use a KdTree to search for the nearest matches in feature space
//        std::cerr<<"Algorithm size: "<<alg3D.size()<<std::endl
//                <<"input cloud size: "<<msg_pcl->size()<<std::endl
//               <<"iteration: "<<i<<std::endl<<std::flush;

//        alg3D[i].setInputCloud(msg_pcl);

////        std::cerr<<"iteration "<<i<<std::endl<<std::flush;

//        // Find the index of the best match for each keypoint, and store it in "correspondences_out"
//        const int k = 1;
//        std::vector<int> k_indices (k);
//        std::vector<float> k_squared_distances (k);

////        std::cerr<<"iteration "<<i<<std::endl<<std::flush;


//        for (size_t j = 0; j < descriptors[i].size()-1; ++j)
//        {
//            pcl::fromROSMsg(descriptors[i][j], *cloud);
//            //            alg3D[i].nearestKSearch (*cloud, j, k, k_indices, k_squared_distances);
//            alg3D[i].radiusSearch(*cloud, j, k, k_indices, k_squared_distances);
//            //            cloud.reset();

//            correspondences_out[j] = k_indices[0];
//            correspondence_scores_out[j] = k_squared_distances[0];
//        }
////        std::cerr<<"iteration "<<i<<std::endl<<std::endl<<std::flush;

//        ratio[i]=std::distance(correspondences_out.begin(), std::max_element(correspondences_out.begin(), correspondences_out.end()));
//    }


//    if (ratio.size()>0)
//        this->matched_object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

//    else
//        this->matched_object_id=-1;


//    return matched_object_id;
//}

int Algorithm3D::get_number_template()
{
    return this->object_number;
}
