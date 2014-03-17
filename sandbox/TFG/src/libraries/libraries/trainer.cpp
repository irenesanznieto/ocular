#include "trainer.h"

Trainer::Trainer()
{
    this->training=false;
    //Load the previously stored templates
    this->descriptors=dataparser.getTemplates();

    //Add the descriptors to each algorithm
    for (unsigned int i =0; i<descriptors.size(); i++)
    {
        alg2D[i].add(this->descriptors[i]);
        alg2D[i].train();
    }
}

int Trainer:: object_number()
{
    //If it is a new object, we want to create a new object position in the vector
    int object_number=descriptors.size();

    //If it is not a new object, we want to add the descriptors to the last object:
    if (new_object!=true)
        object_number-=1;

    return object_number;
}


void Trainer::add_descriptors(const TFG::HandImageConstPtr & msg)
{
    if (this->training==true)
    {
        //convert from ros image msg to opencv image
        cv_bridge::CvImagePtr cv_ptr;
        for (unsigned int i=0; i<msg->image.size(); i++)
        {
            try
            {
                cv_ptr = cv_bridge::toCvCopy(msg->image[i], sensor_msgs::image_encodings::BGR8);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
            }

            cv::Mat image_cv=cv_ptr->image.clone();

            //decide the position of the new view in the matrix of descriptors
            int object_number=this->object_number();

            //add the new view to the descriptors matrix
            descriptors[object_number].push_back(image_cv);

        }
    }
}

//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!
void Trainer::train2D()
{
    if (this->training==true)
    {
        //decide the position of the new view in the matrix of descriptors
        int object_number=this->object_number();

        //add the descriptors vector to the 2D algorithm
        alg2D[object_number].add(descriptors[object_number]);

        //train the 2D algorithm with the new view
        alg2D[object_number].train();

        //store template
        dataparser.save_template_2D(this->descriptors[this->object_number()], this->object_number());

        //store algorithm
        dataparser.save_algorithm_2D(alg2D[this->object_number()], this->object_number());

    }
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
}


void Trainer::set_start_training(bool training)
{
    this->training=training;
}
