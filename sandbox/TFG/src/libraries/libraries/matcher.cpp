#include "matcher.h"

Matcher::Matcher()
{

}

void Matcher :: match()
{
	//match2D

    cv::Mat desc1, desc2;
    float ratio, threshold=300;
    Matcher::flann_comparison(desc1, desc2, ratio, threshold);
	//match3D
	
	//weights between the two
	
	//publish resulting name!
}

void Matcher::match2D()
{

}

std::vector <cv::DMatch> Matcher:: flann_comparison (cv::Mat  &desc1, 	cv::Mat  &desc2, float & ratio, float threshold)
{

    cv::FlannBasedMatcher matcher;

    std::vector< cv::DMatch > matches;

    desc1.convertTo(desc1, CV_32F);
    desc2.convertTo(desc2, CV_32F);


    matcher.match( desc1, desc2, matches );

    //Store good matches, using the threshold ratio
    std::vector< cv::DMatch > good_matches;

    for( int i = 0; i < desc1.rows; i++ )
    {
        if( matches[i].distance < threshold )
            good_matches.push_back( matches[i]);
    }


    //cout <<good_matches.size()<<endl<<matches.size()<<endl;

    //This ratio will help define the correct match for each photo

    ratio=(float)(good_matches.size())/(float)(matches.size());

    return good_matches;
}
