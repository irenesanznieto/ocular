#include "descriptors.h"

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


Mat load_descr (string filename)
{

	FileStorage fr (filename, FileStorage::READ); 
	Mat descriptor; 
	fr["descriptors"]>>descriptor; 

	//Mat A = loadMat("mymat.xml"); // See function loadMat in the question!
	//descriptor.convertTo(descriptor, DataType<float>::type);
	//imshow("TRIAL", descriptor); 
	return descriptor; 

}

vector <KeyPoint> load_keypoints (string filename)
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

		cout <<"Trial!!"<<endl<<saved_name[i]<<endl<< im_path<<endl<<im_data<<endl; 

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
