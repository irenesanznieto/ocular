#include "functions.h"
/*
void capture_image_bs (int number, bool temp)
{

	//Initialization of the needed parameters
    Mat frame, saved_image, fore, back;

    VideoCapture cap(0);
  	cv::BackgroundSubtractorMOG2 bg ;
    bg.set("nmixtures",3);// set number of gaussian mixtures
    bg.set("detectShadows", false); //if false: turn shadow detection off

	int counter=0; 
	bool onetimec=true; 

	//The first thing to do is capture the background to remove it from the final image
	cout << "Locate correctly the web cam and tipe c to continue"<<endl; 
	string ans1; 
	cin >>ans1; 
	if (ans1=="c")
	{

	 	while (counter != number)
		{
		    cap >> frame;

			char key=waitKey(30); 
		
			//if (key=='c' && onetimec==true){
				bg.operator ()(frame,fore, 0);
				bg.getBackgroundImage(back);
			  	cv::erode(fore,fore,cv::Mat());
				cv::dilate(fore,fore,cv::Mat());
				frame.copyTo(fore,fore);
				onetimec=false; 

		   // imshow("CAPTURE OF IMAGES",fore);
			imshow("CAPTURE OF IMAGES", frame); 


			if (key==' ')
			{
				saved_image=fore; 
//				cvDestroyWindow("CAPTURE OF IMAGES");
				templates_extractor(saved_image, temp); 
				counter ++;
			}
		}
	}
	
}

*/

void capture_image (int number, vector <Mat> & cap_images, vector <string> &cap_names)
{
	//Initialization of the needed parameters
    Mat frame;

	cap_images.resize(number); 
	cap_names.resize(number); 

	//namedWindow("CAPTURE"); 
    VideoCapture cap(0);
  	int counter=0; 

	//The first thing to do is capture the background to remove it from the final image
	cout << "Locate correctly the web cam and press the space bar to capture the image"<<endl; 

	 	while (counter < number)
		{
		    cap >> frame;
			imshow("CAPTURE", frame); 
			if (waitKey(30)==' ')
			{
				//the image is stored in the output array
				cap_images[counter]=frame.clone();
				//imwrite("dummy.jpg", cap_images[counter]); 

				//name storage: 
				cout <<"What is the name of the current image?"<<endl; 
				string ans1; 
				cin>> ans1; 
				cap_names[counter]=ans1; 
				counter ++;
			}
		}
		waitKey(20); 
		cvDestroyAllWindows; 
}

vector <DMatch> flann_comparison (Mat  &desc1, 	Mat  &desc2, float & ratio, float threshold)
{

	FlannBasedMatcher matcher;
	vector< DMatch > matches;

	desc1.convertTo(desc1, CV_32F);
	desc2.convertTo(desc2, CV_32F);

	matcher.match( desc1, desc2, matches );

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < desc1.rows; i++ )
	{
		double dist = matches[i].distance;

		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	//cout<<"-- Max dist : "<<max_dist<<endl;
	//cout<<"-- Min dist : "<< min_dist<<endl;


	//Store good matches, using the threshold ratio 
	std::vector< DMatch > good_matches;

	for( int i = 0; i < desc1.rows; i++ )
	{ 
		if( matches[i].distance < threshold*min_dist )
			good_matches.push_back( matches[i]);
	}
	

	//cout <<good_matches.size()<<endl<<matches.size()<<endl; 

	//This ratio will help define the correct match for each photo--> CHECK THIS IS OK!!

	ratio=(float)(good_matches.size())/(float)(matches.size()); 
	//cout << ratio<<endl; 
	return good_matches; 
}

vector <string> getTemplates (string path)
{
		string sys_command="ls "+path +"> ../data/temp/templates.txt";
		system(sys_command.c_str()); 
		
		ifstream file("../data/temp/templates.txt"); 
		string dummy; 
		vector <string> templates; 

		while (file.good())
		{
			getline(file,dummy);
			templates.push_back(dummy); 
		}

		file.close(); 

		templates.erase(templates.end()); //Not sure where this vector creates an empty space in the last row. Anyway, not throwing errors this way neither losing info. 

		return templates; 
		
}


//extract descriptors
void descriptors (Mat & image, Mat & f_descr, vector <KeyPoint> & f_keyp)
{
	Mat  gimage; 

	//read image
	//image=imread(ima);
	cvtColor(image, gimage, CV_BGR2GRAY);

	Mat mask, descriptors;
	vector <KeyPoint> keypoints; 
	
	ORB orb;  
	orb(gimage, mask,  keypoints, descriptors); 
	
	//drawing circles in the keypoints 
/*
	for (int i=0; i<keypoints.size(); i++)
	{
		circle(image, keypoints[i].pt, keypoints[i].size, Scalar(0,0,255), 1); 

	}
*/

	//Assign output variables
	f_descr=descriptors; 
	f_keyp=keypoints;  
	
}

void save_descr(Mat &descriptors, string filename)
{
	filename+= "_d.yml"; 
	FileStorage fs(filename, FileStorage::WRITE);
	fs <<"descriptors"<< descriptors;	
} 

void save_keypoints(vector <KeyPoint> & keyp, string filename)
{
	filename+= "_k.yml"; 
	FileStorage fs(filename, FileStorage::WRITE);
	fs <<"keypoints"<< keyp;	
}


Mat load_desc (string filename)
{

	FileStorage fr (filename, FileStorage::READ); 
	Mat descriptor; 
	fr["descriptors"]>>descriptor; 

	return descriptor; 
}

vector <KeyPoint> load_keyp (string filename)
{
	FileStorage fr (filename, FileStorage::READ); 
	vector <KeyPoint> keypoints; 
	read(fr["keypoints"],keypoints); 
	return keypoints; 
}


void templates_extractor(vector <Mat> &saved_image, vector <string>&saved_name)
{	
	for (int i=0; i<saved_name.size(); i++)
	{
		string im_path="../data/"; 

		string im_data=im_path+saved_name[i]; //path of the xml/yam files
		im_path+= saved_name[i]+".jpg"; //path of the image 

		//save the pattern image--> not necessary, but useful for the final comparison
		imwrite(im_path, saved_image[i]); 

		Mat descriptor; 
		vector <KeyPoint> keypoints;

		//descriptors && keypoints extraction
 
		descriptors (saved_image[i], descriptor, keypoints); 

		save_keypoints(keypoints, im_data);
		save_descr(descriptor, im_data); 
	}
}




