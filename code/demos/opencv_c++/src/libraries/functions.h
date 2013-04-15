#include <iostream>

using namespace std; 

//void capture_image_bs(int);
void capture_image(int, vector <Mat> &, vector <string> &);

vector <DMatch> flann_comparison (Mat & , Mat &, float);

vector <string> getTemplates (string );

//void draw_matches(Mat, Mat,  
