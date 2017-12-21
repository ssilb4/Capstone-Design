#include "makexml.h"

Mat gaussian(Mat inputImg)
{
	/*
	Mat inputImg;

	inputImg = imread(argv, CV_LOAD_IMAGE_COLOR);
	resize(inputImg, inputImg, Size(), 0.3, 0.3, CV_INTER_AREA);
	*/

	Mat noise_image(inputImg.size(), CV_16SC3);
	double average = 0.0;
	double std = 30.0;
	randn(noise_image, Scalar::all(average), Scalar::all(std));

	Mat temp_image;
	inputImg.convertTo(temp_image, CV_16SC3);
	addWeighted(temp_image, 1.0, noise_image, 1.0, 0.0, temp_image);
	temp_image.convertTo(temp_image, inputImg.type());


	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	namedWindow("GaussianNoise", CV_WINDOW_AUTOSIZE);


	moveWindow("Original", 100, 100);
	moveWindow("GaussianNoise", 120, 120);


	//imshow("Original", inputImg);
	//imshow("GaussianNoise", temp_image);

	//waitKey(0);
	return temp_image;
}