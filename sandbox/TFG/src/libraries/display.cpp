#include "display.h"

Display::Display(): it_(nh_)
{

    sub_node="/camera/rgb/image_color";
	image_sub_ = it_.subscribe(sub_node, 1, &Display::display, this);

	WINDOW="Recognition mode";
    cv::namedWindow(WINDOW);
}

Display::~Display()
{
    cv::destroyWindow(WINDOW);
}

void Display::display(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
	  cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
	  ROS_ERROR("cv_bridge exception: %s", e.what());
	  return;
	}

	cv::imshow(WINDOW, cv_ptr->image);

    if (cv::waitKey(3)=='q' ||cv::waitKey(3)==27)
        exit(0);
}



//int main (int argc, char * argv[])
//{
//	ros::init(argc, argv, "track");
//	ImageConverter ic;
//	
//	ros::spin();

//	return 0; 
//}


