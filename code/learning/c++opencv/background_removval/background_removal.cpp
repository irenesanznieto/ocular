#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

//to compile in terminal: g++ background_removal.cpp `pkg-config --cflags --libs opencv` -o background

using namespace cv; 
using namespace std; 

int main ()
{
	Mat back, fore, diff; 
	back=imread("background.jpg"); 
	fore=imread("irene.jpg");

	GaussianBlur(back, back, cv::Size (11, 11), 0);
	GaussianBlur(fore, fore, cv::Size (11, 11), 0);


	absdiff(fore,back,diff);// Absolute differences between the 2 images 
		//cv::threshold(diff,diff,15,255,CV_THRESH_BINARY); // set threshold to ignore small differences you can also use inrange function

	imshow("blurred back", back); 
	imshow ("DIFFERENCE", diff); 
	waitKey(0); 
	return 0; 

}
