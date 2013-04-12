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
	
	DescriptorExtractor * orb; 
	orb=new OrbFeatureDetector; 


	orb->compute(gimage, keypoints, descriptors); 
	delete orb; 

	
	//drawing circles in the keypoints && saving to file
	for (int i=0; i<keypoints.size(); i++)
	{
		circle(image, keypoints[i].pt, keypoints[i].size, Scalar(0,0,255), 1); 

	}

	//FileStorage myfile ("trial.txt"); 
	cvLoad("trial.txt", descriptors);
//void* cvLoad(const char* filename, CvMemStorage* memstorage=NULL, const char* name=NULL, const char** real_name=NULL )¶

	//SHOW IMAGES
	imshow ("Image", image); 
	//imshow ("Grey image", gimage); 

}

/*
void comp_descr()
{
	cv::Mat results;
	cv::Mat dists;
	int k=2; // find the 2 nearest neighbors
	if(objectDescriptors.type()==CV_8U)
	{
		    // Binary descriptors detected (from ORB or Brief)

		    // Create Flann LSH index
		    cv::flann::Index flannIndex(sceneDescriptors, cv::flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);
		    results = cv::Mat(objectDescriptors.rows, k, CV_32SC1); // Results index
		    dists = cv::Mat(objectDescriptors.rows, k, CV_32FC1); // Distance results are CV_32FC1 ?!?!? NOTE OpenCV doc is not clear about that...

		    // search (nearest neighbor)
		    flannIndex.knnSearch(objectDescriptors, results, dists, k, cv::flann::SearchParams() );
	}

}
*/

void save_descr(Mat descriptors)
{
	
} 
