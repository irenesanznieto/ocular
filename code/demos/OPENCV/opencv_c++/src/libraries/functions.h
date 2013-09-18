#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>



using namespace cv; 
using namespace std; 

void capture_image(int, vector <Mat> &, vector <string> &, bool);
void capture_image(int, vector <Mat> &, bool);

vector <DMatch> flann_comparison (Mat & , Mat &,float &,  float);

vector <string> getTemplates (string );



void descriptors (Mat &, Mat &, vector<KeyPoint> &); 
void save_descr(Mat &, string); 
void save_keypoints(vector <KeyPoint> &, string); 

void templates_extractor(vector <Mat> &, vector <string> &); 

Mat  load_desc(string); 
vector <KeyPoint>  load_keyp(string); 

#endif//FUNCTIONS_H

