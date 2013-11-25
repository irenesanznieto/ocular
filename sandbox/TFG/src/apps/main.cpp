#include "../src/libraries/trigger.h"
#include <unistd.h>
#include <iostream>

void instructions();


int main ()
{
	instructions(); 
	Trigger trigger; 
	
	while (1)
	{

		if (trigger.on)
		{
			execlp("learner", "learner", NULL);
			std::cout<<"LEARNING MODE"<<std::endl; 
		}
		else
		{
			execlp("recognizer", "recognizer", NULL);
			std::cout <<"RECOGNITION MODE"<<std::endl; 
		}
	
	}

}

void instructions()
{
	std::cout 	<<"IN-HAND OBJECT LEARNING AND RECOGNITION "<<std::endl
				<<"The default mode is the recognition mode" <<std::endl
				<< "To activate the learning mode, move the hand towards the kinect sensor"<<std::endl; 


}
