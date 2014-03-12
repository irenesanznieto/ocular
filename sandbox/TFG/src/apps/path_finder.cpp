#include <fstream>
#include <iostream>
#include <stdlib.h>

int main ()
{
    std::string sys_command="find . -print | grep 'sandbox/TFG/data/path' > dummy.txt";
    system(sys_command.c_str());

    std::string path;
    std::ifstream myfile;
    myfile.open ("dummy.txt");
    std::getline( myfile, path);
    myfile.close();

    system ("rm dummy.txt");

    std::string complete_path=path+"/"+"path_finder.txt";

    std::ofstream myfile2;
    myfile2.open(complete_path.c_str());
    myfile2<<path;
    myfile2.close();

}

