//TO COMPILE : g++ color_detection.cpp `pkg-config --cflags --libs opencv` -o color_detection

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

 std:: string  detect_color(cv::Mat&); 

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cerr<<"Usage: ./<name_of_executable> <path_to_photo>"<<std::endl; 
		return -1; 
	}
	
	//read the image and store it in a Mat 
	cv:: Mat ROI;   
	ROI = cv::imread( argv[1], 1 );
	//resize the image to half its size so it fits the window
	cv::resize(ROI, ROI, cv::Size(), 0.5,0.5);

	//detect color and write the most predominant in the image
	cv::putText(ROI, detect_color(ROI), cv::Point(10,30), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar::all(0), 2);

	cv:: imshow ( "COLOR DETECTION", ROI); 

	cv::waitKey(0); 

	return 0; 
}

 std:: string  detect_color(cv::Mat& ROI)
{
	//vector that will store the hsv info of the different colors
	std::vector<std::vector <int> > hsv_colors (3) ; 

	//pink	min (HSV) - max (HSV)
	hsv_colors[0].push_back(160);	//H min 
	hsv_colors[0].push_back(100);	//S min 
	hsv_colors[0].push_back(100);	//V min 
	hsv_colors[0].push_back(179);	//H max
	hsv_colors[0].push_back(255);	//S max
	hsv_colors[0].push_back(255);	//V max

	//green min (HSV) - max (HSV)
	hsv_colors[1].push_back(38);
	hsv_colors[1].push_back(0);
	hsv_colors[1].push_back(0);
	hsv_colors[1].push_back(75);
	hsv_colors[1].push_back(50);
	hsv_colors[1].push_back(30);

	//brown min (HSV) - max (HSV)
	hsv_colors[2].push_back(200);
	hsv_colors[2].push_back(20);
	hsv_colors[2].push_back(0);
	hsv_colors[2].push_back(360);
	hsv_colors[2].push_back(70);
	hsv_colors[2].push_back(20);

	//vector that will store the different thresholded images for each color
	std:: vector <cv:: Mat> images (hsv_colors.size()); 

	int white=0, maxwhite=0, maxi=0;
	for (int i=0; i<hsv_colors.size(); i ++)
	{
			//obtain the binary image isolating the chosen color
			cv:: Mat HSV_ROI; 
			cv::cvtColor(ROI, HSV_ROI, CV_BGR2HSV); 
			//threshold the image with the color
			cv::inRange(HSV_ROI,cv::Scalar( hsv_colors[i][0], hsv_colors[i][1], hsv_colors[i][2]), cv::Scalar(hsv_colors[i][3], hsv_colors[i][4], hsv_colors[i][5]), images[i]); 
			//count the white pixels in the image
			white= countNonZero(images[i]);

			//store in maxwhite the largest number of white pixels and in maxi the i for which we have the maxwhite
			if (white > maxwhite)
			{
				maxwhite=white; 
				maxi=i; 
			}

			//show the thresholded images
			std::string name; 
			if (i==0) 
				name= "PINK"; 
			else if (i==1)
				name= "GREEN"; 
			else if (i==2)
				name ="BROWN"; 
			cv::imshow(name, images[i]); 
		
	}

	//std::cout<<maxwhite<<std::endl<<maxi<<std::endl; 
	if (maxwhite<10)
		return "UNKNOWN"; 
	else if (maxi==0) 
		return "PINK"; 
	else if (maxi==1)
		return "GREEN"; 
	else if (maxi==2)
		return "BROWN"; 
	else 
		std:: cerr<<"There isn't any known color in the image"<< std::endl; 
		


}

