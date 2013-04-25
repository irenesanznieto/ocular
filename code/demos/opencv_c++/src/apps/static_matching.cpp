#include "../libraries/functions.h"
#include <stdio.h>


//to know the total time, execute using : time ./name_of_exe

int main (int argc, char * argv[])
{
	cout <<"STATIC RECOGNITION PROGRAM USING OPENCV"<<endl
		 <<"---------------------------------------"<<endl; 

	vector<Mat> im; 
	cout <<"Do you want to use the background substractor? (y/n)"<<endl; 
	string no_back; 
	cin>>no_back; 

	if (no_back=="y")
		capture_image (1, im, true); 
	else
		capture_image (1, im, false); 

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


	for (int i=0; i<temp_keyp.size(); i++)
	{
		final_matches.push_back(flann_comparison(im_desc, temp_desc[i],ratio[i],300)); //obtain the vector with the final matches for every template
	}


	int max_elem=distance(ratio.begin(), max_element (ratio.begin(),ratio.end()));

	//cout <<"Maximum element ratio: "<<max_elem<<endl<<"All element ratios:"<<endl;
	//for (int i=0; i<ratio.size(); i++)
		//cout <<ratio[i]<<endl; 


	Mat temp=imread(names_t[max_elem]); 
	Mat results;

	drawMatches( im[0], im_keyp, temp, temp_keyp[max_elem],final_matches[max_elem], results, Scalar::all(-1), Scalar::all(-1),vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//-- Show detected matches
	string nameofwindow="Matched with: "+names_t[max_elem];
	imshow(nameofwindow , results );
	cvWaitKey(0);
                      
    return 0;
}
