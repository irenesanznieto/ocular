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
	//SHOW IMAGES
	//imshow ("Image", image); 
	//imshow ("Grey image", gimage);


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


void templates_extractor(Mat saved_image)
{	
	string im_path="../data/"; 
	cout <<"What is the name of the current image?"<<endl; 
	string name; 
	cin >> name; 
	string im_data=im_path+name; //path of the xml/yam files
	im_path+= name+".jpg"; //path of the image 

	//save the pattern image--> necessary?!
	imwrite(im_path, saved_image); 


	Mat descriptor; 
	vector <KeyPoint> keypoints;

	//descriptors && keypoints extraction
	descriptors (saved_image, descriptor, keypoints); 
	save_keypoints(keypoints, im_data);
	save_descr(descriptor, im_data); 
}


