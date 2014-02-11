#include "roisegmenter2D.h"

RoiSegmenter2D::RoiSegmenter2D()
{

//    cv::namedWindow("left_hand");
//    cv::namedWindow("right_hand");
}


RoiSegmenter2D::~RoiSegmenter2D()
{
//    cv::destroyAllWindows();

}

TFG::HandImage RoiSegmenter2D::segment(const sensor_msgs::ImageConstPtr & msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    TFG::HandImage final_image;

  if (!coord.points.empty())
    {

        for (unsigned int i=0; i<coord.name.size(); i++){


            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
            }
            //        ROS_ERROR("DEBUG: P1: (%i,%i)  P2: (%i, %i)", coord.data[0],coord.data[1],coord.data[2],coord.data[3]);

            //        Draw a circle to check the position of the hands:
            //        cv::circle(cv_ptr->image, cv::Point(coord.data[0]+abs(coord.data[0]-coord.data[2])/2, coord.data[1]+abs(coord.data[1]-coord.data[3])/2), 10, CV_RGB(255,0,0), 10);

            cv::Mat originalImage=cv_ptr->image.clone();


            int x1, x2, y1, y2;


            if (i==0)
            {
                x1=coord.points[0];
                y1=coord.points[1];
                x2=coord.points[2];
                y2=coord.points[3];
            }
            else if (i==1)
            {
                 x1=coord.points[4];
                 y1=coord.points[5];
                 x2=coord.points[6];
                 y2=coord.points[7];
            }


            RoiSegmenter2D::checkLimits(x1, y1);
            RoiSegmenter2D::checkLimits(x2,y2);

            cv::Point p1(x1,y1);
            cv::Point p2(x2,y2);


            cv::Mat croppedImage=originalImage(cv::Rect(p2, p1));

            cv_ptr->image=croppedImage.clone();


            cv::flip(cv_ptr->image,cv_ptr->image, 1);

            final_image.image.push_back(*cv_ptr->toImageMsg());

            final_image.name.push_back(coord.name[i].data());


//            cv::imshow(final_image.name[i].data()  , cv_ptr->image);
//            cv::waitKey(3);

            cv_ptr->image.release();


        }

       return(final_image);
    }
}

void RoiSegmenter2D::checkLimits(int & x, int& y)
{

    if (x>640)
        x=640;
    else if (x<0)
        x=0;

    if(y>480)
        y=480;
    else if(y<0)
        y=0;
}


void RoiSegmenter2D::coordinates(const TFG::HandLocPxConstPtr &msg)
{
    coord=*msg;
}
