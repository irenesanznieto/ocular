#include "../src/libraries/trigger.h"
#include "../src/libraries/display.h"
#include <unistd.h>
#include <iostream>

void instructions();
void learner();
void recognizer();

int main (int argc, char * argv[])
{
	instructions(); 
	
	ros::init(argc, argv, "TFG");
	Trigger trigger; 
	Display display; 
        
    while (ros::ok())
	{

		if (trigger.on)
		{
			//execlp("learner", "learner", NULL);
			learner(); 
            //std::cout<<"LEARNING MODE"<<std::endl;
		}
		else
		{
			//execlp("recognizer", "recognizer", NULL);
			recognizer(); 
            //std::cout <<"RECOGNITION MODE"<<std::endl;
		}


		ros::spinOnce(); 	
	}
}

void instructions()
{
    std::cout 	<< "IN-HAND OBJECT LEARNING AND RECOGNITION "<<std::endl
                << "The default mode is the recognition mode" <<std::endl
                << "To activate the learning mode, move the hand towards the kinect sensor"<<std::endl
                << "To exit, press q or ESC"<<std::endl;


}

void learner()
{

}

void recognizer()
{

}
