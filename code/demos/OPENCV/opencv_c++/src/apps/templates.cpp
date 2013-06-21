#include "../libraries/functions.h"
#include <stdio.h>


int main()
{
	cout <<"TEMPLATES EXTRACTION PROGRAM USING OPENCV"<<endl
		 <<"-----------------------------------------"<<endl; 
	cout <<"Do you want to erase the previous templates? (y/n)"<<endl; 
			string ans2; 
			cin >> ans2;

	if (ans2=="y")
	{
		system("exec rm -r ../data/*"); //remove all files && folders in that directory
		system("mkdir ../data/temp"); //create a temporal folder
	}

	cout <<"Do you want to use the background substractor? (y/n)"<<endl; 
	string no_back; 
	cin>>no_back; 

	cout << "Enter the number of templates you want to obtain"<<endl;
	int ans3; 
	cin >> ans3;
	cout<<"To capture each new template, press the space bar"<<endl; 

	vector <Mat> templates; 
	vector <string> temp_names;

	if (no_back=="y")
		capture_image(ans3, templates, temp_names,true); 
	else
		capture_image(ans3, templates, temp_names,false); 

	templates_extractor(templates, temp_names); 
}
	
