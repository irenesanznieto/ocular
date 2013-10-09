//TO COMPILE : g++ color_tracking.cpp `pkg-config --cflags --libs opencv` -o color_tracking
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int  isolate_color_hsv(cv::Mat&, cv::Mat&, int [2][3]); 
int  hsv_color(std::string, int [2][3]); 


int main (int argc, char * argv[])
{
	if (argc<2)
	{
		std::cerr<<"Usage: ./<name_of_executable> color"<<std::endl; 
		return (-1); 
	}

	//chose the color to track
	std::string color=argv[1]; 

	//obtain the color to filter from the argument
	int color_number [2][3]; 

	if (hsv_color(color, color_number)== -1)
	{
		std::cerr<<"ERROR: the chosen color is not known"<<std::endl; 
		exit(0); 
	}


	//declare the main variables
	cv:: Mat raw_image, final_image; 
    cv::VideoCapture cap(0);

	if (!cap.isOpened())
        std::cerr << "Cannot open video device" << std::endl;

	while(true)
    {
		//capture the next frame from the camera
        cap >> raw_image;
		cv::flip(raw_image,raw_image,1);

		//isolate the selected color
		isolate_color_hsv(raw_image, final_image,color_number ); 

		//show the original and the processed image
        cv::imshow("Original Image",raw_image);
        cv::imshow("Processed Image",final_image);

        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}

int hsv_color(std::string color, int  color_number[2][3] )
{
	//HSV colors
	int RED_HSV [2][3]={{160,100,100},{179, 255,255}};
	int GREEN_HSV[2][3] = {{38,100,100},{75, 255,255}}; 
	int BLUE_HSV[2][3] = {{75,100,100},{130, 255,255}};
	int YELLOW_HSV[2][3]={{22,100,100},{38,255,255}};
	int ORANGE_HSV[2][3]={{0,100,100},{22,255,255}};
	int VIOLET_HSV[2][3]={{130,100,100},{160,255,255}};

	std::string COLOR=color;
	std::transform(COLOR.begin(), COLOR.end(), COLOR.begin(), ::toupper);

	if (COLOR=="RED") 
		memcpy(color_number, RED_HSV, sizeof(RED_HSV));

	else if (COLOR=="BLUE")
		memcpy(color_number, BLUE_HSV, sizeof(BLUE_HSV));

	else if (COLOR=="GREEN")
		memcpy(color_number, GREEN_HSV, sizeof(GREEN_HSV));

	else if (COLOR=="YELLOW")
		memcpy(color_number, YELLOW_HSV, sizeof(YELLOW_HSV));

	else if (COLOR=="ORANGE")
		memcpy(color_number, ORANGE_HSV, sizeof(ORANGE_HSV));
	else 
		return -1;

	return 0; 
}

int  isolate_color_hsv(cv::Mat& ROI, cv::Mat& final, int color[2][3] )
{
	//obtain the binary image isolating the chosen color
	cv:: Mat HSV_ROI; 
	cv::cvtColor(ROI, HSV_ROI, CV_BGR2HSV); 

	cv::inRange(HSV_ROI,cv::Scalar( color[0][0], color[0][1], color[0][2]), cv::Scalar(color[1][0], color[1][1], color[1][2]), final); 
	
/*	
	int thresh = 100;
	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;

	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using Threshold
	cv::threshold( final, threshold_output, thresh, 255, cv::THRESH_BINARY );

	/// Find contours
	cv::findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

  	 for( int i = 0; i< contours.size(); i++ )
	       	 cv:: drawContours( final, contours, i, cv::Scalar(0,0,255), CV_FILLED, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
*/

	if(final.empty())
	{
		std::cerr<<"Processed image empty"<<std::endl; 
		exit(-1); 
	}
}
