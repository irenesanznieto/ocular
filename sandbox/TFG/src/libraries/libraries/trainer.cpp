#include "trainer.h"


void Trainer::train()
{
	TrainerMatcher::extract_features(); 
	//train 2D features ?? --> not necessary, it is done recursively when the match() function is called
	
}
