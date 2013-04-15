#include "../libraries/ORB/descriptors.h"
#include "../libraries/functions.h"
#include <stdio.h>


//to know the total time, execute using : time ./name_of_exe

int main (int argc, char * argv[])
{

	int ans1=0; 

	do{
		cout <<"OPENCV-C++ DEMO\n ..................\nType 1 to obtain new templates\nType 2 to recognize objects\nType 0 to exit the program\n";
		cin>> ans1;

		if (ans1 == 1)
		{
			cout <<"Do you want to erase the previous templates? (y/n)"<<endl; 
			string ans2; 
			cin >> ans2;

			if (ans2=="y")
			{
				system("exec rm -r ../data/*"); //remove all files && folders in that directory
				system("mkdir ../data/temp"); //create a temporal folder
			}
			
			cout << "Enter the number of templates you want to obtain"<<endl;
			int ans3; 
			cin >> ans3;

			//cout << "Do you want to use the background substractor? (y/n)"<<endl; 
			//string ans4; 
			//cin >> ans4; 

			cout<<"To capture each new template, press the space bar"<<endl; 

			//if (ans4=="y")
			//	capture_image_bs(ans3, false); //false means this is a template 
			//else
				vector <Mat> templates; 
				vector <string> temp_names;

				capture_image(ans3, templates, temp_names); 
				templates_extractor(templates, temp_names); 
		
		}

		if (ans1==2)
		{	
			//capture image to compare: 
			//cout << "Do you want to use the background substractor? (y/n)"<<endl; 
			//string ans5; 
			//cin >> ans5; 

			//if (ans5=="y")
			//	capture_image_bs(1, true);  
			//else
				vector<Mat> comp_image; 
				vector <string> com_name; 
				capture_image (1, comp_image, com_name); 

			//vectors that will store the names of the yam files with the information
			vector <string>keyp_t; 
			vector <string>desc_t; 

			//obtain the templates' information

			keyp_t=getTemplates("../data/*_k.yml"); 
			desc_t=getTemplates("../data/*_d.yml"); 


			//compare the images with the new one
			//for (int i=0; i<templates.size(); i++)
					
		}

	}while (ans1 != 0); 
	
 	waitKey(0);      
	cvDestroyAllWindows();                                 
    return 0;

	

}
