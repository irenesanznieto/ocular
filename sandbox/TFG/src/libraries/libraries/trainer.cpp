#include "trainer.h"

Trainer::Trainer()
{
    //TODO: add the descriptors reading from the files!!

    //Add the descriptors to the algorithm
    dataparser.getTemplates();
    for (unsigned int i =0; i<descriptors.size(); i++)
    {
        alg2D[i].add(descriptors[i]);
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


//REMEMBER TO CHANGE SET_NEW_OBJECT TO TRUE WHENEVER WE ARE LEARNING A NEW OBJECT!!!!!
void Trainer::train(const sensor_msgs::ImageConstPtr & descriptors)
{
    //convert from ros image msg to opencv image
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(descriptors, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }

    //train 2D features
    this->train2D(cv_ptr->image);

    //store template
    dataparser.save_template_2D(this->descriptors[this->object_number()]);

    //store algorithm

    dataparser.save_algorithm_2D(alg2D[this->object_number()], this->object_number());

    //train 3D features


    //store template

    //store algorithm
}


void Trainer::train2D(cv::Mat image_cv)
{
    int object_number=this->object_number();
    descriptors[object_number].push_back(image_cv);
    alg2D[object_number].train();
}








void Trainer ::set_new_object(bool new_object)
{
    this->new_object=new_object;
}







//void save_keypoints(vector <KeyPoint> & keyp, string filename)
//{
//	filename+= "_k.yml";
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs <<"keypoints"<< keyp;
//}

//vector <KeyPoint> load_keyp (string filename)
//{
//	FileStorage fr (filename, FileStorage::READ);
//	vector <KeyPoint> keypoints;
//	read(fr["keypoints"],keypoints);
//	return keypoints;
//}
