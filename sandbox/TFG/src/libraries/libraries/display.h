#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


//Coordinates message
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
 
#include "std_msgs/Int32MultiArray.h"

class Display 
{
	public: 
		
		Display();
		~Display();

        void display(const sensor_msgs::ImageConstPtr& msg);

	private: 
	
		std::string WINDOW; 
		std::string sub_node; 
		ros::NodeHandle nh_;
	  	image_transport::ImageTransport it_;
	  	image_transport::Subscriber image_sub_;
	  	ros::Subscriber coord_sub_;

};

#endif //DISPLAY_H
