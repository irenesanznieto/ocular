#include "algorithm2D.h"

Algorithm2D::Algorithm2D()
{

    //Load the previously stored templates if there are any
    std::cerr<<"GET NUMBER OF TEMPLATES: "<<dataparser.getNumberTemplates()<<std::endl;
    if(dataparser.getNumberTemplates()>1)
    {
        std::cerr<<"1"<<std::endl;
        this->descriptors=dataparser.getTemplates();
        std::cerr<<"1"<<std::endl;
        std::cerr<<"descriptors size"<<descriptors.size()<<std::endl;

        alg2D.resize(descriptors.size());

        //Add the descriptors to each algorithm & train them
        for (unsigned int i =0; i<descriptors.size(); i++)
        {
            try
            {
                alg2D[i].add(this->descriptors[i]);
                alg2D[i].train();
            }
            catch (std::exception & e)
            {}
        }
        std::cerr<<"1"<<std::endl;

    }

    matched_object_id=-1;
    this->object_number=0;


}



void Algorithm2D::add_descriptors(const TFG::HandImageConstPtr & msg)
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
        image_cv.convertTo(image_cv,CV_32F );

        descriptors[this->object_number].push_back(image_cv);
    }
}

//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!
void Algorithm2D::train2D()
{
    try{

//        if (descriptors[this->object_number].size()>0)
//        {
            //add the descriptors vector to the 2D algorithm
            //        ROS_ERROR("OBJECT NUMBER %d DESCRIPTORS SIZE %d ALGORITHMS SIZE %d", object_number, descriptors.size(), alg2D.size());

            alg2D[this->object_number].add(descriptors[this->object_number]);

            //train the 2D algorithm with the new view
            alg2D[this->object_number].train();
//        }

    }
    catch (std::exception & e)
    {}

    //store template
    dataparser.save_template_2D(this->descriptors[this->object_number], this->object_number);

    //store algorithm
    dataparser.save_algorithm_2D(alg2D[this->object_number], this->object_number);


}


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

//        alg2D.resize(alg2D.size()+1);
//        descriptors.resize(descriptors.size()+1);

    }

    this->object_number=alg2D.size()-1;



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
            cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        //threshold used in the flann_comparison
        float  threshold=300;

        //compare FLANN
        matched_object_id=this->flann_comparison(cv_ptr->image, threshold);
    }

    return matched_object_id;
}

int Algorithm2D:: flann_comparison (cv::Mat  &desc1,float threshold)
{
    //vector that will store the ratios of similarity between the new image and the templates
    std::vector< float> ratio;
    //resize the vector
    ratio.resize(alg2D.size());

    //vector to store the distances between descriptors
    std::vector<std::vector< cv::DMatch > >matches;
    //resize the vector
    matches.resize(descriptors.size());

    //Store good matches, using the threshold ratio
    std::vector<std::vector< cv::DMatch > >good_matches;
    good_matches.resize(descriptors.size());


    std::cerr<<"In flann_comparison function, alg2d.size(): "<<alg2D.size()<<std::endl<<"descriptors.size(): "<<descriptors.size()<<std::endl<< "descriptors[object_number].size(): "<<descriptors[object_number].size()<<std::endl;

    //for each algorithm, match the new descriptors with the algorithm's information
    for (unsigned int object_number=0; object_number<alg2D.size(); object_number++)
    {
        desc1.convertTo(desc1, CV_32F);


        //match each algorithm with the new cv::Mat and output the result in the matches vector
        alg2D[object_number].match( desc1, matches[object_number]);


        std::cerr<<"Number of matches: "<<matches[object_number].size()<<std::endl;

        //decide which are the good matches (i.e. matches whose distance is lower than the threshold) of the above matches
        for( unsigned int i = 0; i < matches[object_number].size(); i++ )
        {
            std::cerr<<"iteration"<<i<<std::endl;

            if( matches[object_number][i].distance < threshold )
                good_matches[object_number].push_back( matches[object_number][i]);
        }


        //cout <<good_matches.size()<<endl<<matches.size()<<endl;

        //The ratio is defined as the number of good_matches  over the number of total matches
        //This ratio is defined for each algorithm. Since each algorithm will be used for each object, this will be the similarity with this object
        if (matches[object_number].size() >0)
        {
            std::cerr<<"1"<<std::endl;

            ratio[object_number]=(float)(good_matches[object_number].size()/matches[object_number].size());

            std::cerr<<"1"<<std::endl;
        }
        else
        {
            ratio[object_number]=-1;
        }

        std::cerr<<"Comparison with object "<<object_number<<" ratio: "<<ratio[object_number]<< "division: "<<(good_matches[object_number].size()/matches[object_number].size())<<std::endl;

    }


    //Obtain the object ID as the vector position with the maximum of the ratios
    int object_id=std::distance(ratio.begin(),std::max_element(ratio.begin(), ratio.end()));

    return object_id;
}
