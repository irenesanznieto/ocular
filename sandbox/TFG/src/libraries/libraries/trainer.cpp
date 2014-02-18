#include "trainer.h"

Trainer::Trainer()
{

    //TODO: add the descriptors reading from the files!!

    //Add the descriptors to the algorithm
    alg2D.add(descriptors);
    alg2D.train();
}

void Trainer::train(const sensor_msgs::PointCloud2ConstPtr & pc_msg, const sensor_msgs::ImageConstPtr & image_msg)
{
    //convert from ros image msg to opencv image
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(image_msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }


    //train 2D features
    this->train2D(cv_ptr->image);

    //store template
    this->save_template();

    //store algorithm
    this->save_algorithm();


    //train 3D features


    //store template

    //store algorithm
}


void Trainer::train2D(cv::Mat image_cv)
{
    descriptors.push_back(image_cv);
    alg2D.train();
}


void Trainer::save_template()
{

}

void Trainer::save_algorithm()
{

}

//std::vector <cv::DMatch>  flann_comparison (cv::Mat  &desc1, 	cv::Mat  &desc2, float & ratio, float threshold)
//{

//    cv::FlannBasedMatcher matcher;

//    std::vector< cv::DMatch > matches;

//    desc1.convertTo(desc1, CV_32F);
//    desc2.convertTo(desc2, CV_32F);

//    matcher.match( desc1, desc2, matches );

//    //Store good matches, using the threshold ratio
//    std::vector< cv::DMatch > good_matches;

//    for( int i = 0; i < desc1.rows; i++ )
//    {
//        if( matches[i].distance < threshold )
//            good_matches.push_back( matches[i]);
//    }


//    //cout <<good_matches.size()<<endl<<matches.size()<<endl;

//    //This ratio will help define the correct match for each photo

//    ratio=(float)(good_matches.size())/(float)(matches.size());

//    return good_matches;
//}




//void save_descr(Mat &descriptors, string filename)
//{
//	filename+= "_d.yml";
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs <<"descriptors"<< descriptors;
//}

//void save_keypoints(vector <KeyPoint> & keyp, string filename)
//{
//	filename+= "_k.yml";
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs <<"keypoints"<< keyp;
//}


//Mat load_desc (string filename)
//{
//	FileStorage fr (filename, FileStorage::READ);
//	Mat descriptor;
//	fr["descriptors"]>>descriptor;

//	return descriptor;
//}

//vector <KeyPoint> load_keyp (string filename)
//{
//	FileStorage fr (filename, FileStorage::READ);
//	vector <KeyPoint> keypoints;
//	read(fr["keypoints"],keypoints);
//	return keypoints;
//}

