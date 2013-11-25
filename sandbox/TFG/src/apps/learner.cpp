#include <iostream>
#include "../src/libraries/trigger.h"

void instructions();


int main ()
{
	instructions(); 
	Trigger trigger; 
	
	while (1)
	{
				
		if (trigger.on==false)
		{
			return 0; 
		}
	
	}
}

void instructions()
{
	std::cout 	<<"LEARNING MODE"<<std::endl
				<<"To end the learning mode, move the hand towards your body" <<std::endl;
}
