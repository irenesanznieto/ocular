#include "algorithm2D.h"

Algorithm2D::Algorithm2D()
{
    //Initialize the matched_object_id to -1 until a match is found
    matched_object_id=-1;

    //Initialize object_number to 0 so if there are no previous templates, the first object has ID 0
    this->object_number=0;
    descriptors.resize(1);
    alg2D.resize(1);
}

Algorithm2D::~Algorithm2D()
{
    std::cerr<<std::endl<<"[LearnerRecognizer -- Algorithm2D]   SAVING TEMPLATES 2D: "<<std::endl<<std::flush;
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
//        std::cerr<<"Descriptors[i].size: "<<descriptors[i].size()<<std::endl
//                << "number_views: "<<number_views<<std::endl<<std::flush;
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


void Algorithm2D::set_number_views (int number_views)
{
    this->number_views=number_views;
}


void Algorithm2D::load_templates()
{

    if(dataparser.getNumberTemplates("2D")>1)
    {
        dataparser.getTemplates(number_views,this->descriptors);
        this->next_object();

        this->alg2D.resize(descriptors.size());

        std::cerr<<std::endl<<"[LearnerRecognizer -- Algorithm2D]   LOADED "<<descriptors.size()-1<< " TEMPLATES 2D "<<std::endl<<std::endl<<std::flush;
    }
}

int Algorithm2D::get_number_views ()
{
    return this->number_views;
}


void Algorithm2D::next_object()
{
    descriptors.push_back(std::vector<cv::Mat> ());
    alg2D.push_back(cv::FlannBasedMatcher ());
    this->object_number=descriptors.size()-1;
}

bool Algorithm2D::add_descriptors( TFG::HandImage msg)
{
    //convert from ros image msg to opencv image
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg.image[0], sensor_msgs::image_encodings::MONO8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }

    cv::Mat image_cv=cv_ptr->image.clone();

//    std::cerr<<"add descriptors 2D "<<std::endl<<std::flush;


    //add the new view to the descriptors matrix
    image_cv.convertTo(image_cv,CV_32F);

    //        std::cerr<<"adding descriptors in object_number: "<<object_number<<std::endl;
    if(image_cv.empty())
        return -1;
    if(!image_cv.empty())
    {
        descriptors[this->object_number].push_back(image_cv);
        return 0;
    }

}

//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!


void Algorithm2D ::set_new_object(bool new_object)
{
    this->new_object=new_object;
}




int Algorithm2D :: match(const TFG::HandImageConstPtr & msg)
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
    for (unsigned int object_number=0; object_number<descriptors.size()-1; object_number++)
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

int Algorithm2D::get_number_template()
{
    return this->object_number;
}
