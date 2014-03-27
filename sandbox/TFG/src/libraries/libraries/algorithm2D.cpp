#include "algorithm2D.h"

Algorithm2D::Algorithm2D()
{
    //Initialize the matched_object_id to -1 until a match is found
    matched_object_id=-1;

    //Initialize object_number to 0 so if there are no previous templates, the first object has ID 0
    this->object_number=0;

}

//Algorithm2D::Algorithm2D(int number_views)
//{
//    this->number_views=number_views;

//    //    std::cerr<<"GET NUMBER OF TEMPLATES: "<<dataparser.getNumberTemplates()<<std::endl;

//    //Load the previously stored templates if there are any
//    if(dataparser.getNumberTemplates()>1)
//    {
//        this->descriptors=dataparser.getTemplates();
//    }

//    for (unsigned int i=0; i<descriptors.size(); i++)
//        std::cerr<<"template: "<<i<<" , number of views: "<<descriptors[i].size()<<std::endl;

//    Algorithm2D();
//}


Algorithm2D::~Algorithm2D()
{
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        while (descriptors[i].size()< this->number_views)
        {
            //            std::cerr<<"Object: "<<i<<"descriptor[i].size(): "<<descriptors[i].size()<<std::endl;
            descriptors[i].push_back(descriptors[i][0]);
        }
        dataparser.save_template_2D(descriptors[i],i);
        std::cerr<<"template: "<<i<<" , number of views: "<<descriptors[i].size()<<std::endl;
    }
}


void Algorithm2D::set_number_views (int number_views)
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

    this->alg2D.resize(descriptors.size());

        std::cerr<<"descriptors.size(): "<<descriptors.size()<<std::endl;
    std::cerr<<"Object number after setting number of views: "<<this->object_number<<std::endl;



}


int Algorithm2D::get_number_views ()
{
    return this->number_views;
}


void Algorithm2D::add_descriptors(const TFG::HandImageConstPtr & msg, int number_view)
{

    //convert from ros image msg to opencv image
    cv_bridge::CvImagePtr cv_ptr;
    for (unsigned int i=0; i<msg->image.size(); i++)
    {
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::MONO8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        cv::Mat image_cv=cv_ptr->image.clone();

        //        ROS_ERROR("OBJECT NUMBER %d DESCRIPTORS SIZE %d", object_number, descriptors.size());

        //add the new view to the descriptors matrix
        image_cv.convertTo(image_cv,CV_32F);

        std::cerr<<"adding descriptors in object_number: "<<object_number<<std::endl;
        descriptors[this->object_number].push_back(image_cv);
    }
}

//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!



//void Algorithm2D::train3D ()
//{
//    //train 3D features

//    //store template

//    //store algorithm
//}

void Algorithm2D ::set_new_object(bool new_object)
{
    this->new_object=new_object;

    if(this->new_object)
    {
        descriptors.push_back(std::vector<cv::Mat> ());
        alg2D.push_back(cv::FlannBasedMatcher ());

        //        std::cerr<<"descriptors & alg2D size: "<<descriptors.size()<<" "<<alg2D.size()<<std::endl;
    }

    this->object_number=descriptors.size()-1;
}




int Algorithm2D :: match2D(const TFG::HandImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;

    //resulting object id

    for (unsigned int i=0; i<msg->image.size(); i++)
    {
        //transform from ROS msg to OpenCV msg
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg->image[i],sensor_msgs::image_encodings::MONO8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        //threshold used in the flann_comparison
        float  threshold=300;

        try{

            //compare FLANN
            matched_object_ratio=this->flann_comparison(cv_ptr->image, threshold);
        }
        catch(std::exception & e)
        {}
    }

    return matched_object_id;
}

int Algorithm2D:: flann_comparison (cv::Mat  desc1,float threshold)
{
    //vector that will store the ratios of similarity between the new image and the templates
    std::vector< float> ratio;


    //resize the vector
    ratio.resize(descriptors.size());


    //vector to store the distances between descriptors
    std::vector<std::vector< cv::DMatch > >matches;



    //resize the vector
    matches.resize(descriptors.size());



    //Store good matches, using the threshold ratio
    std::vector<std::vector< cv::DMatch > >good_matches;
    good_matches.resize(descriptors.size());


    //    std::cerr<<"In flann_comparison function, alg2d.size(): "<<alg2D.size()<<std::endl<<"descriptors.size(): "<<descriptors.size()<<std::endl<< "descriptors[object_number].size(): "<<descriptors[object_number].size()<<std::endl;

    //for each algorithm, match the new descriptors with the algorithm's information
    for (unsigned int object_number=0; object_number<descriptors.size(); object_number++)
    {
        desc1.convertTo(desc1, CV_32F);

        //        std::cerr<<"descriptors[object_number].size(): "<<descriptors[object_number].size()<<std::endl;

        for (unsigned int j=0; j<descriptors[object_number].size(); j++)
        {
            //            std::cerr<<"object_number: "<<object_number<<" j: "<<j<<std::endl;

            //match each algorithm with the new cv::Mat and output the result in the matches vector
            //            std::cerr<<"desc1.type: "<<desc1.type()<<"  descriptors[][].type: "<<descriptors[object_number][j].type()<<std::endl;
            alg2D[object_number].match( desc1,descriptors[object_number][j], matches[object_number]);
            //            std::cerr<<"Iteration number "<<object_number<<std::endl;

        }

        //        std::cerr<<"Number of matches: "<<matches[object_number].size()<<std::endl;

        //decide which are the good matches (i.e. matches whose distance is lower than the threshold) of the above matches
        for( unsigned int i = 0; i < matches[object_number].size(); i++ )
        {
            if( matches[object_number][i].distance < threshold )
                good_matches[object_number].push_back( matches[object_number][i]);
        }


        //cout <<good_matches.size()<<endl<<matches.size()<<endl;

        //The ratio is defined as the number of good_matches  over the number of total matches
        //This ratio is defined for each algorithm. Since each algorithm will be used for each object, this will be the similarity with this object



        if (matches[object_number].size()>0)
        {
            ratio[object_number]=(float)(good_matches[object_number].size())/(float)(matches[object_number].size());
        }
        else if (matches[object_number].size()<=0)
        {
            ratio[object_number]=-1;
        }

        //        std::cerr<<"Comparison with object "<<object_number<<" ratio: "<<ratio[object_number]<<std::endl;

    }
    //Obtain the object ID as the vector position with the maximum of the ratios
    this->matched_object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

    //    std::cerr<<"Ratio recognized object: "<<ratio[this->matched_object_id]<<std::endl;
    return ratio[this->matched_object_id];
}
