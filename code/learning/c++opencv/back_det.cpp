#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
 
//to compile in terminal: g++ back_det.cpp `pkg-config --cflags --libs opencv` -o back_det

int main(int argc, char *argv[])
{
    cv::Mat frame;
    cv::Mat back;
    cv::Mat fore;
    cv::VideoCapture cap(0);
    cv::BackgroundSubtractorMOG2 bg ;
    bg.set("nmixtures",3);// set number of gaussian mixtures
    bg.set("detectShadows", true); //if false: turn shadow detection off


    std::vector<std::vector<cv::Point> > contours;
 
    
    for(;;)
    {
        cap >> frame;
        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);
      	cv::erode(fore,fore,cv::Mat());
        cv::dilate(fore,fore,cv::Mat());
        //cv::findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
        //cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);

		frame.copyTo(fore,fore);
		

        cv::imshow("Frame",frame);
        cv::imshow("Foreground",fore);
		cv::imshow("Background", back); 
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}
