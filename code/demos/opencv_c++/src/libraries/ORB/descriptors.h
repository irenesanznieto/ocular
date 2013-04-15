#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

using namespace std; 
using namespace cv;

void descriptors (Mat &, Mat &, vector<KeyPoint> &); 
void save_descr(Mat &, string); 
void save_keypoints(vector <KeyPoint> &, string); 

void templates_extractor(vector <Mat> &, vector <string> &); 

Mat  load_descr(string); 
vector <KeyPoint>  load_keypoints(string); 

#endif //DESCRIPTORS_H
