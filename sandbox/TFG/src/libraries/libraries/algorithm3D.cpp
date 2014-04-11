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


void Algorithm3D::load_templates()
{
    if(dataparser.getNumberTemplates("3D")>1)
    {
        dataparser.getTemplates(number_views,this->descriptors);
        this->next_object();

        this->alg3D.resize(descriptors.size());

        std::cerr<<std::endl<<"[LearnerRecognizer -- Algorithm3D]   LOADED "<<descriptors.size()-1<< " TEMPLATES 2D "<<std::endl<<std::endl<<std::flush;
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
    std::cerr<<"match3D"<<std::endl<<std::flush;

    //transform to pcl format
    pcl::PointCloud<pcl::PFHSignature125>::Ptr msg_pcl (new pcl::PointCloud<pcl::PFHSignature125> ());
    pcl::fromROSMsg(*msg, *msg_pcl);


    pcl::PointCloud<pcl::PFHSignature125>::Ptr cloud (new pcl::PointCloud<pcl::PFHSignature125> ());

    std::vector<int> ratio;
    ratio.resize(descriptors.size());


    //segmentation fault here :S xD:

    //match3D
    for (unsigned int i=0; i<alg3D.size(); i++)
    {

        std::cerr<<"iteration "<<i<<std::endl<<std::flush;

        // Resize the output vector
        std::vector<int> correspondences_out;
        std::vector<float> correspondence_scores_out;

        std::cerr<<"iteration "<<i<<std::endl<<std::flush;

        correspondences_out.resize (descriptors[i].size ());
        correspondence_scores_out.resize (descriptors[i].size ());

        std::cerr<<"iteration "<<i<<std::endl<<std::flush;

        // Use a KdTree to search for the nearest matches in feature space
        std::cerr<<"Algorithm size: "<<alg3D.size()<<std::endl
                <<"input cloud size: "<<msg_pcl->size()<<std::endl<<std::flush;

        if (msg_pcl->size()<10000)  //to avoid errors?? check
            alg3D[i].setInputCloud(msg_pcl);

        std::cerr<<"iteration "<<i<<std::endl<<std::flush;

        // Find the index of the best match for each keypoint, and store it in "correspondences_out"
        const int k = 1;
        std::vector<int> k_indices (k);
        std::vector<float> k_squared_distances (k);

        std::cerr<<"iteration "<<i<<std::endl<<std::flush;


        for (size_t j = 0; j < descriptors[i].size (); ++j)
        {
            pcl::fromROSMsg(descriptors[i][j], *cloud);
            //            alg3D[i].nearestKSearch (*cloud, j, k, k_indices, k_squared_distances);
            alg3D[i].radiusSearch(*cloud, j, k, k_indices, k_squared_distances);
            //            cloud.reset();

            correspondences_out[j] = k_indices[0];
            correspondence_scores_out[j] = k_squared_distances[0];
        }
        std::cerr<<"iteration "<<i<<std::endl<<std::endl<<std::flush;

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
