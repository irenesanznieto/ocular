#include "dataparser.h"

DataParser::DataParser()
{
    //    try{
    pkg_main_path=get_path_to_pkg();
    //    }
    //    catch (std::length_error  e)
    //    {
    //        ROS_ERROR("EXCEPTION 1");
    //    }
    algorithms_2D_path=pkg_main_path+"/data/algorithms/2D/";


    algorithms_3D_path=pkg_main_path+"/data/algorithms/3D/";
    templates_path=pkg_main_path+"/data/templates/";
    temp_path=pkg_main_path+"/data/temp.txt";


    //create the templates folder
    std::string mkdir="mkdir ";
    std::string dummy=mkdir+templates_path;
    system(dummy.c_str());

    //    //create the algorithms folder
    //    dummy=mkdir+algorithms_2D_path;
    //    dummy.erase(dummy.end()-3, dummy.end());
    //    system(dummy.c_str());

    //    //create the algorithms 2D folder
    //    dummy=mkdir+algorithms_2D_path;
    //    system(dummy.c_str());

    //    //create the algorithms 3D folder
    //    dummy=mkdir+algorithms_3D_path;
    //    system(dummy.c_str());

}


std::string DataParser::get_path_to_pkg()
{
    //search for a certain library in order to obtain the full path
    //    std::string sys_command="find . -print | grep 'sandbox/TFG/src/libraries/libraries/dataparser.h' > ~/dummy.txt";
    //    system(sys_command.c_str());

    //    std::string path;
    //    std::ifstream myfile;
    //    myfile.open ("~/dummy.txt");
    //    std::getline( myfile, path);
    //    myfile.close();

    //    system ("rm ~/dummy.txt");

    //    //remove the last part (/src/libraries/libraries/dataparser.h)
    //    path.erase(path.end()-37, path.end());

    //    //remove the beginning (./)
    //    path.erase(path.begin(), path.begin()+2);


    std::string path="/home/peko/tfg_git/sandbox/TFG";

    return path;
}

std::vector <std::string> DataParser::get_file_names (std::string path)
{

    //Store the names of the files in the string path in the file specified by temp_path
    std::string sys_command="ls "+path +"> "+temp_path;
    system(sys_command.c_str());

    //Open the temp file
    std::ifstream file(temp_path.c_str());
    std::string dummy;
    std::vector <std::string> templates;


    //Get each line and store the names in a vector
    while (file.good())
    {
        getline(file,dummy);
        templates.push_back(path+dummy);
    }
    //Close the temp file
    file.close();

    //Remove the temp file
    std::string remove_temp_files="rm "+temp_path;

    system(remove_temp_files.c_str());


    //Remove the last element of the vector which is not complete [due to getline function]
    //    templates.erase(templates.end());

    //Return the vector of strings with the file names
    return templates;
}


void DataParser::save_template_2D(std::vector<cv::Mat> & descriptors, int number_object)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path<<templates_path<<number_object;

    //    //        std::cerr<<"path: "<<path.str()<<"templates_path: "<<templates_path<<"number_object: "<<number_object<<std::endl;

    //    //create a folder in the templates_path with the number of the position of the object in the vector
    //    std::stringstream command;
    //    command<<"mkdir "<<path.str();
    //    system(command.str().c_str());

    std::stringstream filename;
    //Store each matrix of descriptors corresponding to different views of the object in a different yml file inside the same object's folder
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        //remove the contents of the stringstream filename for the next iteration
        filename.str(std::string());

        //add the path to the filename
        filename<<path.str();
        //add the name of the file depending on the number of view and also the extension
        filename<<"_2D_view_"<<i<<"_d.yml";

        //        std::cerr<<"FILENAME: "<<filename.str()<<std::endl;
        //write the descriptors to the filestorage
        this->save_descriptor(descriptors[i], filename.str());
    }
}


void DataParser::save_template_2D(cv::Mat descriptors, int number_object, int number_view)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path<<templates_path<<number_object;

    //        std::cerr<<"path: "<<path.str()<<"templates_path: "<<templates_path<<"number_object: "<<number_object<<std::endl;

    //create a folder in the templates_path with the number of the position of the object in the vector
    std::stringstream command;
    command<<"mkdir "<<path.str();
    system(command.str().c_str());

    std::stringstream filename;

    //remove the contents of the stringstream filename for the next iteration
    filename.str(std::string());

    //add the path to the filename
    filename<<path.str();
    //add the name of the file depending on the number of view and also the extension
    filename<<"/view_"<<number_view<<"_d.yml";

    //        std::cerr<<"FILENAME: "<<filename.str()<<std::endl;
    //write the descriptors to the filestorage
    this->save_descriptor(descriptors, filename.str());
}


void DataParser::save_template_3D(std::vector<sensor_msgs::PointCloud2> & descriptors, int number_object)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path<<templates_path<<number_object;

    //    //        std::cerr<<"path: "<<path.str()<<"templates_path: "<<templates_path<<"number_object: "<<number_object<<std::endl;

    //    //create a folder in the templates_path with the number of the position of the object in the vector
    //    std::stringstream command;
    //    command<<"mkdir "<<path.str();
    //    system(command.str().c_str());

    std::stringstream filename;
    //Store each matrix of descriptors corresponding to different views of the object in a different yml file inside the same object's folder
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        //remove the contents of the stringstream filename for the next iteration
        filename.str(std::string());

        //add the path to the filename
        filename<<path.str();
        //add the name of the file depending on the number of view and also the extension
        filename<<"_3D_view_"<<i<<"_d.pcd";

        //        std::cerr<<"FILENAME: "<<filename.str()<<std::endl;
        //write the descriptors to the filestorage
        this->save_descriptor(descriptors[i], filename.str());
    }

}

void DataParser::save_descriptor(sensor_msgs::PointCloud2 &descriptors, std::string filename)
{
    pcl::io::savePCDFile(filename, descriptors);
}


void DataParser::save_descriptor(cv::Mat &descriptors, std::string filename)
{
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs <<"descriptors"<< descriptors;
}

void DataParser::save_algorithm_2D(cv::FlannBasedMatcher & alg2D, int object_number)
{
    std::stringstream filename;
    filename<<algorithms_2D_path<<object_number<<".yml";

    cv::FileStorage fs(filename.str(), cv::FileStorage::WRITE);
    alg2D.write(fs);
}


std::vector<cv::FlannBasedMatcher > DataParser::load_algorithms_2D()
{
    //Get the file names in the algorithms2D path
    std::vector <std::string> algorithms=this->get_file_names(algorithms_2D_path);

    if (algorithms.size()>0)
    {
        std::vector<cv::FlannBasedMatcher >alg2D;
        for (unsigned int i=0; i<algorithms.size(); i++)
        {
            cv::FileStorage fr(algorithms[i], cv::FileStorage::READ);
            cv::FileNode fn;
            fn.fs=*fr;
            alg2D[i].read(fn);

        }
        return alg2D;
    }
}


cv::Mat DataParser::load_descriptor (std::string filename)
{

    cv::FileStorage fr (filename, cv::FileStorage::READ);
    cv::Mat descriptor;

    fr["descriptors"]>>descriptor;

    descriptor.convertTo(descriptor, CV_32F);

    return descriptor;
}

int DataParser:: getNumberAlgorithms()
{
    return this->get_folder_number_of_items(algorithms_2D_path);
}

int DataParser:: getNumberTemplates()
{
    return this->get_folder_number_of_items(templates_path);
}

int DataParser::get_folder_number_of_items(std::string path)
{
    return this->get_file_names(path).size();
}


void DataParser:: getTemplates (int number_views, std::vector<std::vector<cv::Mat> > & descriptors)
{
    //obtain the names of all the objects in the templates folder [the names of all the folders, i.e. the ID of all the objects learned]
    std::vector<std::string> templates=this->get_file_names(templates_path);
    if(templates.size()>0)
    {
        //the number of objects is the size of the previous vector
        int total_objects=templates.size()/number_views;

        std::stringstream path;

        //the size of the descriptors matrix will be the same as the objects in the folder
        descriptors.resize(total_objects);


        int object_number=0;
        int counter=0;
        for (int j=0; j<total_objects; j++ )
        {
            //extract the information from the yml files of each view of each object [number of views equal to the size of the vector templates containing the names of the files in that folder]
            for (unsigned int i=0; i<number_views; i++)
            {
                //                std::cerr<<"object: "<<object_number<<" view "<<i<<" name: "<<templates[counter]<<std::endl;
                descriptors[j].push_back(this->load_descriptor(templates[counter]));

                if(i==number_views-1)
                    object_number++;

                counter++;
            }

            //            std::cerr<<"descriptors[j].size(): "<<descriptors[j].size()<<std::endl;
        }

        //        std::cerr<<"dataparser: descriptors.size(): "<<descriptors.size()<<std::endl;

    }
}



void DataParser:: getTemplates (int number_views, std::vector<std::vector<sensor_msgs::PointCloud2> > & descriptors)
{
//    //obtain the names of all the objects in the templates folder [the names of all the folders, i.e. the ID of all the objects learned]
//    std::vector<std::string> templates=this->get_file_names(templates_path);
//    if(templates.size()>0)
//    {
//        //the number of objects is the size of the previous vector
//        int total_objects=templates.size()/number_views;

//        std::stringstream path;

//        //the size of the descriptors matrix will be the same as the objects in the folder
//        descriptors.resize(total_objects);


//        int object_number=0;
//        int counter=0;
//        for (int j=0; j<total_objects; j++ )
//        {
//            //extract the information from the yml files of each view of each object [number of views equal to the size of the vector templates containing the names of the files in that folder]
//            for (unsigned int i=0; i<number_views; i++)
//            {
//                //                std::cerr<<"object: "<<object_number<<" view "<<i<<" name: "<<templates[counter]<<std::endl;
//                descriptors[j].push_back(this->load_descriptor(templates[counter]));

//                if(i==number_views-1)
//                    object_number++;

//                counter++;
//            }

//            //            std::cerr<<"descriptors[j].size(): "<<descriptors[j].size()<<std::endl;
//        }

//        //        std::cerr<<"dataparser: descriptors.size(): "<<descriptors.size()<<std::endl;

//    }
}



