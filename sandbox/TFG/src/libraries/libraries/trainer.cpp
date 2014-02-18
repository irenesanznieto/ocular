#include "trainer.h"

Trainer::Trainer()
{
    //Vector descriptors that will store the descriptors dataset
    const std::vector<cv::Mat> descriptors;
    //TODO: add the descriptors reading from the files!!

    //Add the descriptors to the algorithm
    alg2D.add(descriptors);
    alg2D.train();
}

void Trainer::train(const sensor_msgs::PointCloud2ConstPtr & pc_msg, const sensor_msgs::ImageConstPtr & image_msg)
{

    //train 2D features
    this->train2D(alg2D);

    //store template
    this->save_template();

    //store algorithm
    this->save_algorithm();


    //train 3D features


    //store template

    //store algorithm
}


void Trainer::train2D(cv::FlannBasedMatcher & alg2D)
{


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

