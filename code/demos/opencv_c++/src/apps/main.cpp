#include "../libraries/functions.h"
#include <stdio.h>


//to know the total time, execute using : time ./name_of_exe

int main (int argc, char * argv[])
{

	string ans1; 

	do{
		cout <<"OPENCV-C++ DEMO\n ..................\nType TEMPLATES to obtain new templates\nType RECOGNIZE to recognize objects\nType EXIT to exit the program\n";
		cin>> ans1;

		if (ans1 == "TEMPLATES" || ans1=="templates")
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
			cout<<"To capture each new template, press the space bar"<<endl; 

			vector <Mat> templates; 
			vector <string> temp_names;

			capture_image(ans3, templates, temp_names); 
			templates_extractor(templates, temp_names); 
	
		}

		else if (ans1 == "RECOGNIZE" || ans1=="recognize")
		{		

			vector<Mat> im; 
			vector <string> im_name;
			capture_image (1, im, im_name); 

			Mat im_desc; //NEW IMAGE descriptors
			vector <KeyPoint> im_keyp; //NEW IMAGE keypoints
			descriptors(im[0], im_desc, im_keyp); 
		
			//vectors that will store the names of the yam files with the information
			vector <string> names_t; 
			vector <string> keyp_t; 
			vector <string> desc_t; 
 
			vector <Mat> temp_desc; //TEMPLATES descriptors
			vector <vector <KeyPoint> >temp_keyp; //TEMPLATES keypoints

			//obtain the templates' names
			keyp_t=getTemplates("../data/*_k.yml"); 
			desc_t=getTemplates("../data/*_d.yml"); 
			names_t=getTemplates("../data/*.jpg"); 


			//extract the information from the yml files
			for (int i=0; i<keyp_t.size(); i++)
			{			
				temp_desc.push_back(load_desc(desc_t[i])); 
				temp_keyp.push_back(load_keyp(keyp_t[i])); 
			}


			vector <vector <DMatch> > final_matches; 
			vector<float> ratio; 

			ratio.resize(temp_keyp.size()); 
			

			//SEGMENTATION FAULT HERE U.u again... and again... :(

			for (int i=0; i<temp_keyp.size(); i++)
			{
				final_matches.push_back(flann_comparison(im_desc, temp_desc[i],ratio[i], 10)); //obtain the vector with the final matches for every template
			}

		
			int max_elem=distance(ratio.begin(), max_element (ratio.begin(),ratio.end()));
			
			cout <<max_elem<<endl; 

			Mat temp=imread(names_t[max_elem]); 
			imshow ("jelou", temp);
		  	Mat results;
		




		  	drawMatches( im[0], im_keyp, temp, temp_keyp[max_elem],final_matches[max_elem], results, Scalar::all(-1), Scalar::all(-1),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	  //-- Show detected matches
	  		imshow( "RESULTS", results );

	/*
	  for( int i = 0; i < (int)final_matches.size(); i++ )
	  { 
		cout<< "-- Good Match ["<<i<<"] Keypoint 1: "<<final_matches[i].queryIdx<<"  -- Keypoint 2: "<< final_matches[i].trainIdx<<endl;

	  }
	*/
					
		}

	}while (ans1 != "EXIT" && ans1 != "exit"); 
                      
    return 0;
}
