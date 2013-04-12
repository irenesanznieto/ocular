#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

//to compile in terminal: g++ main.cpp `pkg-config --cflags --libs opencv` -o main

using namespace std; 
using namespace cv; 

int main (int argc, char * argv[])
{
	ORB a;
	//void ORB::operator()(InputArray image, InputArray mask, vector<KeyPoint>& keypoints, OutputArray descriptors, bool useProvidedKeypoints=false ) const

	Mat image, gimage; 
	Mat mask; 
	vector <KeyPoint> keypoints; 
	
	image=imread("../templates_data/template0.jpg");
	cvtColor(image, gimage, CV_BGR2GRAY);

	//a(image, 
	imshow ("Image", image); 
	imshow ("Grey image", gimage); 
	
 	waitKey(0);                                      
    return 0;

	

}
