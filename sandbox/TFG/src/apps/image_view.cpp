#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <TFG/HandImage.h>

class ImageConverter
{
    ros::NodeHandle nh_;
    //  image_transport::ImageTransport it_;
    ros::Subscriber image_sub_;

public:
    ImageConverter()
    //    : it_(nh_)
    {
        cv::namedWindow("left_hand");
        cv::namedWindow("right_hand");
        // Subscrive to input video feed and publish output video feed
        image_sub_ = nh_.subscribe<TFG::HandImage>("image", 1,&ImageConverter::imageCb, this);
    }


    ~ImageConverter()
    {
        cv::destroyAllWindows();

    }

    void imageCb(const TFG::HandImageConstPtr& msg)
    {


        cv_bridge::CvImagePtr cv_ptr;
        for(unsigned int i=0; i<msg->image.size(); i++)
        {

            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
            }

            // Update GUI Window

            cv::imshow(msg->name[i].data()  , cv_ptr->image);
            cv::waitKey(3);
            cv_ptr->image.empty();
        }


    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_view");
    ImageConverter ic;
    ros::spin();
    return 0;
}

