#pragma once
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>
#include <opencv2/core.hpp>
#include <vector> 
#include <cstdio>
#include <opencv2\opencv.hpp>
#include <iomanip>
#include <chrono>
#include <random>

using namespace std;
using namespace cv;

void makexml(string folder, string filename, string imgtype, string name, int width, int height, int xmin, int xmax, int ymin, int ymax);
Mat alpha(Mat foreground, Mat background, Mat alpha, int location[]);
Mat gaussian(Mat inputImg);
Mat argument(Mat input, int x[], int y[], int result_x[], int result_y[]);
