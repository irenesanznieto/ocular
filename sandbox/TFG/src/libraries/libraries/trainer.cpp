#include "trainer.h"

Trainer::Trainer()
{
    //TODO: add the descriptors reading from the files!!

    //Add the descriptors to the algorithm
    getTemplates();
    for (unsigned int i =0; i<descriptors.size(); i++)
    {
        alg2D[i].add(descriptors[i]);
        alg2D[i].train();
    }
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
    this->save_template_2D();

    //store algorithm
    this->save_algorithm_2D();




    //train 3D features


    //store template

    //store algorithm
}


void Trainer::train2D(cv::Mat image_cv)
{
    //If it is a new object, we want to create a new object position in the vector
    int object_number=descriptors.size();

    //If it is not a new object, we want to add the descriptors to the last object:
    if (new_object!=true)
        object_number-=1;


    descriptors[object_number].push_back(image_cv);
    alg2D[object_number].train();
}


void Trainer::save_template_2D()
{
    //If it is a new object, we want to create a new object position in the vector
    int object_number=descriptors.size();

    //If it is not a new object, we want to add the descriptors to the last object:
    if (new_object!=true)
        object_number-=1;

    //NAME CODE:
    std::stringstream filename;
    filename <<"../data/templates/"<<object_number<<"/";

    std::stringstream command;
    command<<"mkdir "<<filename;

    if (new_object==true)
        system(command.str().c_str());

    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        filename<<"view_"<< i<<"_d.yml";
        cv::FileStorage fs(filename.str(), cv::FileStorage::WRITE);
        fs <<"descriptors"<< descriptors[object_number][i];

    }
}

void Trainer::save_algorithm_2D()
{
    //If it is a new object, we want to create a new object position in the vector
    int object_number=descriptors.size();

    //If it is not a new object, we want to add the descriptors to the last object:
    if (new_object!=true)
        object_number-=1;

//    cv::FlannBasedMatcher trial;
    std::stringstream filename;
    filename<<"../data/algorithms/2D/"<<object_number<<".yml";

    cv::FileStorage fs(filename.str(), cv::FileStorage::WRITE);
    alg2D[object_number].write(fs);

}


void Trainer ::set_new_object(bool new_object)
{
    this->new_object=new_object;
}


std::vector <std::string> Trainer::get_file_names (std::string path)
{
    std::string sys_command="ls "+path +"> ../data/temp/temp.txt";
    system(sys_command.c_str());

    std::ifstream file("../data/temp/temp.txt");
    std::string dummy;
    std::vector <std::string> templates;

    while (file.good())
    {
        getline(file,dummy);
        templates.push_back(dummy);
    }

    file.close();
    system("rm ../data/temp/temp.txt");

    templates.erase(templates.end());
}



void Trainer:: getTemplates ()
{

    std::vector<std::string> number_of_objects_folders=get_file_names("../data/templates/");
    int total_objects=number_of_objects_folders.size();


    std::stringstream path;
    path<<"../data/templates/";

    for (int object_number=0;object_number<total_objects; object_number++ )
    {
        path<<object_number<<"/";
        std::vector <std::string> templates=get_file_names(path.str());

        //extract the information from the yml files
        for (int i=0; i<templates.size(); i++)
        {
            descriptors[object_number].push_back(this->load_descriptor(templates[i]));
            //            temp_keyp.push_back(load_keypoint(keyp_t[i]));
        }
    }

}


//std::vector <cv::DMatch>  flann_comparison (cv::Mat  &desc1, 	cv::Mat  &desc2, float & ratio, float threshold)
//{

//    cv::FlannBasedMatcher matcher;

//    std::vector< cv::DMatch > matches;

//    desc1.convertTo(desc1, CV_32F);
//    desc2.convertTo(desc2, CV_32F);

//    matcher.match( desc1, desc2, matches );

//    //Store good matches, using the threshold ratio
//    std::vector< cv::DMatch > good_matches;

//    for( int i = 0; i < desc1.rows; i++ )
//    {
//        if( matches[i].distance < threshold )
//            good_matches.push_back( matches[i]);
//    }


//    //cout <<good_matches.size()<<endl<<matches.size()<<endl;

//    //This ratio will help define the correct match for each photo

//    ratio=(float)(good_matches.size())/(float)(matches.size());

//    return good_matches;
//}




//void save_descr(Mat &descriptors, string filename)
//{
//	filename+= "_d.yml";
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs <<"descriptors"<< descriptors;
//}

//void save_keypoints(vector <KeyPoint> & keyp, string filename)
//{
//	filename+= "_k.yml";
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs <<"keypoints"<< keyp;
//}


cv::Mat Trainer::load_descriptor (std::string filename)
{
    cv::FileStorage fr (filename, cv::FileStorage::READ);
    cv::Mat descriptor;
    fr["descriptors"]>>descriptor;

    return descriptor;
}

//vector <KeyPoint> load_keyp (string filename)
//{
//	FileStorage fr (filename, FileStorage::READ);
//	vector <KeyPoint> keypoints;
//	read(fr["keypoints"],keypoints);
//	return keypoints;
//}

