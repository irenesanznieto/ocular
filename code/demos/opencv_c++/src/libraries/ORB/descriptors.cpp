#include "descriptors.h"

//extract descriptors
void descriptors (string ima)
{
	Mat image, gimage; 

	//read image
	image=imread(ima);
	cvtColor(image, gimage, CV_BGR2GRAY);

	Mat mask, descriptors;
	vector <KeyPoint> keypoints; 
	ORB a;

	a(gimage, mask, keypoints, descriptors, false); 


	

	for (int i=0; i<keypoints.size(); i++)
	{
		circle(image, keypoints[i].pt, keypoints[i].size, Scalar(0,0,255), 1); 
	}
	//Circle(img, center, radius, color, thickness=1, lineType=8, shift=0) → None

	//void ORB::operator()(InputArray image, InputArray mask, vector<KeyPoint>& keypoints, OutputArray descriptors, bool useProvidedKeypoints=false ) const


	//SHOW IMAGES
	imshow ("Image", image); 
	//imshow ("Grey image", gimage); 

}
