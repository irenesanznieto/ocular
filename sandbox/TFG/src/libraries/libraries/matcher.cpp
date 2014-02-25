#include "matcher.h"

Matcher::Matcher()
{

}

void Matcher :: match()
{
	//match2D

    cv::Mat desc1, desc2;
    float ratio, threshold=300;
    Matcher::flann_comparison(desc1, desc2, ratio, threshold);
	//match3D
	
	//weights between the two
	
	//publish resulting name!
}

void Matcher::match2D()
{

}

std::vector <cv::DMatch> Matcher:: flann_comparison (cv::Mat  &desc1, 	cv::Mat  &desc2, float & ratio, float threshold)
{

    cv::FlannBasedMatcher matcher;

    std::vector< cv::DMatch > matches;

    desc1.convertTo(desc1, CV_32F);
    desc2.convertTo(desc2, CV_32F);


    matcher.match( desc1, desc2, matches );

    //Store good matches, using the threshold ratio
    std::vector< cv::DMatch > good_matches;

    for( int i = 0; i < desc1.rows; i++ )
    {
        if( matches[i].distance < threshold )
            good_matches.push_back( matches[i]);
    }


    //cout <<good_matches.size()<<endl<<matches.size()<<endl;

    //This ratio will help define the correct match for each photo

    ratio=(float)(good_matches.size())/(float)(matches.size());

    return good_matches;
}



void Matcher::load_algorithms_2D(std::string path)
{
    //path = "../data/algorithms/2D/";
    std::vector <std::string> algorithms=get_file_names(path);
    //    cv::FlannBasedMatcher trial;
    std::string name_algorithm;

    for (unsigned int i=0; i<algorithms.size(); i++)
    {
        cv::FileStorage fr(algorithms[i], cv::FileStorage::READ);
//        name_algorithm="algorithm"+i;
//        alg2D[i].read(fr);

        cv::FileNode fn;
        fn.fs=*fr;
        alg2D[i].read(fn);
//        fr[name_algorithm]>>alg2D[i];
//        cv::read(fr[name_algorithm],alg2D[i]);
//        alg2D[i].read(fr);
    }
}


cv::Mat Matcher::load_descriptor (std::string filename)
{
    cv::FileStorage fr (filename, cv::FileStorage::READ);
    cv::Mat descriptor;
    fr["descriptors"]>>descriptor;

    return descriptor;
}

void Matcher:: getTemplates ()
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
        for (unsigned int i=0; i<templates.size(); i++)
        {
            descriptors[object_number].push_back(this->load_descriptor(templates[i]));
            //            temp_keyp.push_back(load_keypoint(keyp_t[i]));
        }
    }
}

std::vector <std::string> Matcher::get_file_names (std::string path)
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

    return templates;
}
