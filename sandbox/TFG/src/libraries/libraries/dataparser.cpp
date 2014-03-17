#include "dataparser.h"

DataParser::DataParser()
{
    pkg_main_path=get_path_to_pkg();
    algorithms_2D_path=pkg_main_path+"/data/algorithms/2D/";
    algorithms_3D_path=pkg_main_path+"/data/algorithms/3D/";
    templates_path=pkg_main_path+"/data/templates/";
    temp_path=pkg_main_path+"/data/temp/temp.txt";
}


std::string DataParser::get_path_to_pkg()
{
    //search for a certain library in order to obtain the full path
    std::string sys_command="find . -print | grep 'sandbox/TFG/src/libraries/libraries/function.h' > dummy.txt";
    system(sys_command.c_str());

    std::string path;
    std::ifstream myfile;
    myfile.open ("dummy.txt");
    std::getline( myfile, path);
    myfile.close();

    system ("rm dummy.txt");

    //remove the last part (/src/libraries/libraries/function.h)
    path.erase(path.end()-35, path.end());

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
    templates.erase(templates.end());

    //Return the vector of strings with the file names
    return templates;
}


void DataParser::save_template_2D(std::vector<cv::Mat> & descriptors, int number_object)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path <<templates_path<<number_object;

    //create a folder in the templates_path with the number of the position of the object in the vector
    std::stringstream command;
    command<<"mkdir "<<path;
    system(command.str().c_str());

    std::stringstream filename;
    //Store each matrix of descriptors corresponding to different views of the object in a different yml file inside the same object's folder
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        //add the path to the filename
        filename<<path;
        //add the name of the file depending on the number of view and also the extension
        filename<<"/"<<"view_"<< i<<"_d.yml";
        //create the filestorage
        cv::FileStorage fs(filename.str(), cv::FileStorage::WRITE);
        //write the descriptors to the filestorage
        fs <<"descriptors"<< descriptors[i];
        //remove the contents of the stringstream filename for the next iteration
        filename.str(std::string());
    }
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


cv::Mat DataParser::load_descriptor (std::string filename)
{
    cv::FileStorage fr (filename, cv::FileStorage::READ);
    cv::Mat descriptor;
    fr["descriptors"]>>descriptor;

    return descriptor;
}


std::vector<std::vector<cv::Mat> > DataParser:: getTemplates ()
{
    //obtain the names of all the objects in the templates folder [the names of all the folders, i.e. the ID of all the objects learned]
    std::vector<std::string> number_of_objects_folders=this->get_file_names(templates_path);
    //the number of objects is the size of the previous vector
    int total_objects=number_of_objects_folders.size();

    std::stringstream path;

    //the size of the descriptors matrix will be the same as the objects in the folder
    std::vector<std::vector<cv::Mat> >descriptors;
    descriptors.resize(total_objects);


    for (int object_number=0;object_number<total_objects; object_number++ )
    {
        //initialize the stringstream
        path.str(std::string());
        //add the path of the templates and the object folder
        path<<templates_path<<object_number<<"/";
        //get the file names of each object folder
        std::vector <std::string> templates=get_file_names(path.str());

        //extract the information from the yml files of each view of each object [number of views equal to the size of the vector templates containing the names of the files in that folder]
        for (unsigned int i=0; i<templates.size(); i++)
        {
            descriptors[object_number].push_back(load_descriptor(templates[i]));
            //            temp_keyp.push_back(load_keypoint(keyp_t[i]));
        }
    }

    return descriptors;
}


