#include "matcher.h"

Matcher::Matcher()
{
    this->algorithms2D= dataparser.load_algorithms_2D();
}

int Matcher :: match2D(const TFG::HandImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    int object_id;
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

void Matcher::match3D()
{
    //match3D
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
