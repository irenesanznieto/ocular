#include "../libraries/ORB/descriptors.h"
#include "../libraries/functions.h"
#include <stdio.h>

//to know the total time, execute using : time ./name_of_exe


int main (int argc, char * argv[])
{
	cout <<"OPENCV-PYTHON DEMO\n ..................\nType 1 to obtain new templates\nType 2 to recognize objects\n";
	int ans1; 
	cin>> ans1; 

	if (answer == 1)
	{
		cout <<"Do you want to erase the previous templates? (y/n)"<<endl; 
		string ans2; 
		cin >> ans2;

		if (templates=="y")
			system("exec rm -r ../data/*"); 
			
		cout << "Enter the number of templates you want to obtain"<<endl;
		int ans3; 
		cin >> ans3;

		cout<<"To capture each new template, press the space bar"<<endl; 
		capture_image (answer); 
		
	}

	if (answer ==2)
	{
	
	capture_image(1); //capture image
	 
	


	}
	
 	waitKey(0);                                      
    return 0;

	

}
