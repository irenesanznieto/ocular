#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
 
using namespace cv; 
using namespace std; 


int main(int argc, char *argv[])
{

	class myBackgroundSubstractor: public BackgroundSubtractorMOG2
	{
	public:
		void setbackgroundRatio(float a){backgroundRatio = a;}
	};

    Mat frame;
    Mat back;
    Mat fore;
    VideoCapture cap(0);
	cap.set(CV_CAP_PROP_BRIGHTNESS,1);


    myBackgroundSubstractor bg ;
    bg.set("nmixtures",3);// set number of gaussian mixtures
    bg.set("detectShadows", true); //if false: turn shadow detection off
	bg.setbackgroundRatio(0.0001);
    std::vector<std::vector<cv::Point> > contours;
 

	fore.convertTo(fore, CV_32S); 
    
RNG rng(12345);

    for(;;)
    {
        cap >> frame;
        bg.operator ()(frame,fore);
        //bg.getBackgroundImage(back);
      	//erode(fore,fore,cv::Mat());
        //dilate(fore,fore,cv::Mat());
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
        drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);

		frame.copyTo(fore,fore);

       // drawContours(frame,hull,-1,cv::Scalar(0,255,0),2);

/*
//HULL

	Mat src_copy = fore.clone();
	Mat src_gray;
	cvtColor(src_copy, src_gray, CV_BGR2GRAY);
	Mat threshold_output;
	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold( src_gray, threshold_output, 2, 255, THRESH_BINARY );

	/// Find contours
	findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	/// Find the convex hull object for each contour
	vector<vector<Point> >hull( contours.size() );
	for( size_t i = 0; i < contours.size(); i++ )
	 {   convexHull( Mat(contours[i]), hull[i], false ); }

	/// Draw contours + hull results
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( size_t i = 0; i< contours.size(); i++ )
	 {
	   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	   drawContours( drawing, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
	   drawContours( drawing, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
	 }

	/// Show in a window
	namedWindow( "Hull demo", WINDOW_AUTOSIZE );
	imshow( "Hull demo", drawing );






//HULL

*/



        imshow("Foreground",fore);

        if(waitKey(30) >= 0) break;
    }


    return 0;
}
