#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#include "ORB/descriptors.h"

using namespace cv; 
using namespace std; 

void capture_image (int number)
{
    Mat frame, saved_image, fore, back;

    VideoCapture cap(0);
  	cv::BackgroundSubtractorMOG2 bg ;
    bg.set("nmixtures",3);// set number of gaussian mixtures
    bg.set("detectShadows", true); //if false: turn shadow detection off

	int counter=0; 
	cout << "Locate correctly the web cam and tipe continue to continue"<<endl; 
	string response; 
	cin >>response;
	if (response=="continue"){
 	while (counter != number)
    {
        cap >> frame;
	    bg.operator ()(frame,fore);
	    bg.getBackgroundImage(back);
	  	cv::erode(fore,fore,cv::Mat());
	    cv::dilate(fore,fore,cv::Mat());
		frame.copyTo(fore,fore);

        imshow("CAPTURE OF IMAGES",frame);

		if (waitKey(30) == ' ')
		{
			saved_image=fore; 
			cvDestroyWindow("CAPTURE OF IMAGES");
			templates_extractor(saved_image); 
			counter ++;
		}
    }
	}
}

vector <DMatch> flann_comparison (Mat  &desc1, 	Mat  &desc2, float threshold)
{

  FlannBasedMatcher matcher;
  vector< DMatch > matches;
  desc1.convertTo(desc1, CV_32F);
  desc2.convertTo(desc2, CV_32F);
  matcher.match( desc1, desc2, matches );

  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for( int i = 0; i < desc1.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  cout<<"-- Max dist : "<<max_dist<<endl;
  cout<<"-- Min dist : "<< min_dist<<endl;

  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
  //-- PS.- radiusMatch can also be used here.
  std::vector< DMatch > good_matches;

  for( int i = 0; i < desc1.rows; i++ )
  { if( matches[i].distance < threshold*min_dist )
    { good_matches.push_back( matches[i]); }

	}

	cout <<"Number of drawn matches over number of total matches"<< (float)good_matches.size()/(float)matches.size() <<endl; 	
	return good_matches; 
}





