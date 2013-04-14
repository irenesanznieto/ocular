#include "../libraries/ORB/descriptors.h"
#include "../libraries/functions.h"

int main (int argc, char * argv[])
{
	if (argc <2)
	{
		cerr << "Usage: ./executable_name	 path_to_photo1/photo1.extension_photo1	 path_to_photo2/photo2.extension_photo2 "<<endl; 
	}

	cout <<"ORB DESCRIPTORS EXTRACTOR AND FLANN BASED MATCHER"<<endl; 
	
	//Read images directly to grayscale: 
	Mat img1 = imread( argv[1] );
 	Mat img2 = imread( argv[2] );

	Mat desc1, desc2; 
	vector<KeyPoint>keyp1, keyp2; 

	//Descriptor extraction: 

	descriptors (img1, desc1, keyp1); 
	descriptors(img2, desc2, keyp2);   
	
	



  //Draw good matches: 

  vector <DMatch> final_matches=flann_comparison(desc1, desc2, 10);
  Mat img_matches;
  drawMatches( img1, keyp1, img2, keyp2,final_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );



  //-- Show detected matches
  imshow( "Good Matches", img_matches );

  for( int i = 0; i < (int)final_matches.size(); i++ )
  { 
	cout<< "-- Good Match ["<<i<<"] Keypoint 1: "<<final_matches[i].queryIdx<<"  -- Keypoint 2: "<< final_matches[i].trainIdx<<endl;

  }



	
 	waitKey(0);                                      
    return 0;

}
