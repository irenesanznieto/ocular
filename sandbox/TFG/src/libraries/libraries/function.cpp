#include "function.h"

std::string get_path_to_pkg()
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
