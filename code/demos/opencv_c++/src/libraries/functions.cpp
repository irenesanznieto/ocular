#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <fstream>
#include "ORB/descriptors.h"


using namespace cv; 
using namespace std; 

/*
void capture_image_bs (int number, bool temp)
{

	//Initialization of the needed parameters
    Mat frame, saved_image, fore, back;

    VideoCapture cap(0);
  	cv::BackgroundSubtractorMOG2 bg ;
    bg.set("nmixtures",3);// set number of gaussian mixtures
    bg.set("detectShadows", false); //if false: turn shadow detection off

	int counter=0; 
	bool onetimec=true; 

	//The first thing to do is capture the background to remove it from the final image
	cout << "Locate correctly the web cam and tipe c to continue"<<endl; 
	string ans1; 
	cin >>ans1; 
	if (ans1=="c")
	{

	 	while (counter != number)
		{
		    cap >> frame;

			char key=waitKey(30); 
		
			//if (key=='c' && onetimec==true){
				bg.operator ()(frame,fore, 0);
				bg.getBackgroundImage(back);
			  	cv::erode(fore,fore,cv::Mat());
				cv::dilate(fore,fore,cv::Mat());
				frame.copyTo(fore,fore);
				onetimec=false; 

		   // imshow("CAPTURE OF IMAGES",fore);
			imshow("CAPTURE OF IMAGES", frame); 


			if (key==' ')
			{
				saved_image=fore; 
//				cvDestroyWindow("CAPTURE OF IMAGES");
				templates_extractor(saved_image, temp); 
				counter ++;
			}
		}
	}
	
}

*/

void capture_image (int number, vector <Mat> & cap_images, vector <string> &cap_names)
{
	//Initialization of the needed parameters
    Mat frame;

	cap_images.resize(number); 
	cap_names.resize(number); 

	namedWindow("CAPTURE"); 
    VideoCapture cap(0);
  	int counter=0; 

	//The first thing to do is capture the background to remove it from the final image
	cout << "Locate correctly the web cam and press the space bar to capture the image"<<endl; 

	 	while (1)
		{
		    cap >> frame;
			imshow("CAPTURE", frame); 
			if (waitKey(30)==' ')
			{
				//the image is stored in the output array
				cap_images[counter]=frame.clone();
				//imwrite("dummy.jpg", cap_images[counter]); 

				//name storage: 
				cout <<"What is the name of the current image?"<<endl; 
				string ans1; 
				cin>> ans1; 
				cap_names[counter]=ans1; 
				counter ++;
				if (counter == number)
					break; 
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

vector <string> getTemplates (string path)
{
		string sys_command="ls "+path +"> ../data/temp/templates.txt";
		system(sys_command.c_str()); 

		ifstream file("../data/temp/templates.txt"); 

		vector <string> templates; 
		int i=0; 
		while (file.is_open())
		{
			getline (file,templates[i]);
			i++; 
		}
		file.close(); 
		return templates; 
		
}




