#include "dataparser.h"

DataParser::DataParser()
{
    pkg_main_path=get_path_to_pkg();

    algorithms_2D_path=pkg_main_path+"/data/algorithms/2D/";


    algorithms_3D_path=pkg_main_path+"/data/algorithms/3D/";
    templates_path_2D=pkg_main_path+"/data/templates/2D/";
    templates_path_3D=pkg_main_path+"/data/templates/3D/";
    temp_path=pkg_main_path+"/data/temp.txt";


    //create the templates folder
    std::string mkdir="mkdir -p ";
    std::string dummy=mkdir+templates_path_2D;
    system(dummy.c_str());

    dummy=mkdir+templates_path_3D;
    system(dummy.c_str());
}

std::string DataParser::getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return  std::string( result, (count > 0) ? count : 0 );
}

std::string DataParser::get_path_to_pkg()
{
    std::string path=getexepath();
    path.erase(path.end()-23, path.end());
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
    path<<templates_path_2D<<number_object;

    //    //create a folder in the templates_path with the number of the position of the object in the vector


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

        //write the descriptors to the filestorage
        this->save_descriptor(descriptors[i], filename.str());

    }
}


//2D
void DataParser::save_template(cv::Mat descriptors, int number_object, int number_view)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path<<templates_path_2D<<number_object;

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

    //write the descriptors to the filestorage
    this->save_descriptor(descriptors, filename.str());
}

//3D
void DataParser::save_template(std::vector<
        pcl::PCLPointCloud2 > & descriptors, int number_object)
{
    //NAME CODE:
    std::stringstream path;

    //The name of the file will be a number [the position of the object in the vector of descriptors]
    path<<templates_path_3D<<number_object;

    std::stringstream filename;
    for (unsigned int i=0; i<descriptors.size(); i++)
    {
        //remove the contents of the stringstream filename for the next iteration
        filename.str(std::string());

        //add the path to the filename
        filename<<path.str();
        //add the name of the file depending on the number of view and also the extension
        filename<<"_3D_view_"<<i<<"_d.pcd";
        //write the descriptors to the filestorage
        this->save_descriptor(descriptors[i], filename.str());
    }

}

void DataParser::save_descriptor(
        pcl::PCLPointCloud2  &descriptors, std::string filename)
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
//    filename<<algorithms_2D_path<<object_number<<".yml";
    filename<<algorithms_2D_path<<object_number<<".xml";

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



        pcl::PCLPointCloud2  DataParser::load_descriptor3D(std::string filename)
{

        pcl::PCLPointCloud2  descriptors;
    pcl::PointCloud<pcl::PFHSignature125> descriptors_pcl;
    pcl::io::loadPCDFile(filename, descriptors_pcl);

    pcl::toROSMsg(descriptors_pcl, descriptors);

    return descriptors;
}

int DataParser:: getNumberAlgorithms()
{
    return this->get_folder_number_of_items(algorithms_2D_path);
}

int DataParser:: getNumberTemplates(std::string type)
{
    if (type=="2D")
        return this->get_folder_number_of_items(templates_path_2D);
    else if (type=="3D")
        return this->get_folder_number_of_items(templates_path_2D);
    else
        std::cerr<<"[ LearnerRecognizer --> DataParser ]    UNKNOWN template type"<<std::endl<<std::flush;
}

int DataParser::get_folder_number_of_items(std::string path)
{
    return this->get_file_names(path).size();
}


//2D
void DataParser:: getTemplates (int number_views, std::vector<std::vector<cv::Mat> > & descriptors)
{
    //obtain the names of all the objects in the templates folder [the names of all the folders, i.e. the ID of all the objects learned]
    std::vector<std::string> templates=this->get_file_names(templates_path_2D);
    templates.erase(templates.end());

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
                descriptors[j].push_back(this->load_descriptor(templates[counter]));

                if(i==number_views-1)
                    object_number++;

                counter++;
            }
        }
    }
}


//3D
void DataParser:: getTemplates (int number_views, std::vector<std::vector<
        pcl::PCLPointCloud2 > > & descriptors)
{
    //obtain the names of all the objects in the templates folder [the names of all the folders, i.e. the ID of all the objects learned]
    std::vector<std::string> templates=this->get_file_names(templates_path_3D);
    templates.erase(templates.end());


    if(templates.size()>0)
    {
        //the number of objects is the size of the previous vector
        int total_objects=templates.size()/number_views;


        std::stringstream path;

        //the size of the descriptors matrix will be the same as the objects in the folder
        descriptors.resize(total_objects);


        pcl::PCLPointCloud2  a;

        int counter=0;

        for (int j=0; j<total_objects; j++ )
        {
            //extract the information from the yml files of each view of each object [number of views equal to the size of the vector templates containing the names of the files in that folder]
            for (unsigned int i=0; i<number_views; i++)
            {
                descriptors[j].push_back(this->load_descriptor3D(templates[counter]));
                counter++;
            }

        }
    }
}
