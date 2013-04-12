#include "libraries/ORB/descriptors.h"
//to compile in terminal: g++ main.cpp `pkg-config --cflags --libs opencv` -o main 

int main (int argc, char * argv[])
{
	descriptors("../templates_data/template0.jpg"); 
	
 	waitKey(0);                                      
    return 0;

	

}
