#include "trainer.h"

Trainer::Trainer()
{
    //Load the previously stored templates if there are any
    if(dataparser.getNumberTemplates()>0)
    {
        this->descriptors=dataparser.getTemplates();

        //Add the descriptors to each algorithm & train them
        for (unsigned int i =0; i<descriptors.size(); i++)
        {
            alg2D[i].add(this->descriptors[i]);
            alg2D[i].train();
        }
    }
}


void Trainer::add_descriptors(const TFG::HandImageConstPtr & msg)
{

    //convert from ros image msg to opencv image
    cv_bridge::CvImagePtr cv_ptr;
    for (unsigned int i=0; i<msg->image.size(); i++)
    {
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8/*sensor_msgs::image_encodings::TYPE_8UC1*/);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }

        cv::Mat image_cv=cv_ptr->image.clone();

        //decide the position of the new view in the matrix of descriptors
//        int object_number=this->object_number();
//        ROS_ERROR("OBJECT NUMBER %d DESCRIPTORS SIZE %d", object_number, descriptors.size());

        //add the new view to the descriptors matrix
        descriptors[this->object_number].push_back(image_cv);

    }
}

//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!
void Trainer::train2D()
{
    //decide the position of the new view in the matrix of descriptors
//    int object_number=this->object_number();

    //add the descriptors vector to the 2D algorithm
    ROS_ERROR("OBJECT NUMBER %d DESCRIPTORS SIZE %d ALGORITHMS SIZE %d", object_number, descriptors.size(), alg2D.size());

    alg2D[this->object_number].add(descriptors[this->object_number]);

    ROS_ERROR("3");
    //train the 2D algorithm with the new view
    alg2D[this->object_number].train();

    ROS_ERROR("4");
    //store template
    dataparser.save_template_2D(this->descriptors[this->object_number], this->object_number);

    ROS_ERROR("5");

    //store algorithm
    dataparser.save_algorithm_2D(alg2D[this->object_number], this->object_number);


}


void Trainer::train3D ()
{
    //train 3D features

    //store template

    //store algorithm
}

void Trainer ::set_new_object(bool new_object)
{
    this->new_object=new_object;

    if(this->new_object)
    {
        descriptors.push_back(std::vector<cv::Mat> ());
        alg2D.push_back(cv::FlannBasedMatcher ());
    }

    this->object_number=descriptors.size()-1;

}
