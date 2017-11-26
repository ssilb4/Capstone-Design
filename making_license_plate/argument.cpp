#include "makexml.h"

Mat argument(Mat input, int x[], int y[], int result_x[], int result_y[])
{
	//랜덤
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 ranNum(seed);
	int one_X = ranNum() % (input.cols/2) , one_Y = ranNum() % (input.rows / 2), 
		two_X = ranNum() % (input.cols / 2), two_Y = ranNum() % (input.rows / 2), 
		three_X = ranNum() % (input.cols / 2), three_Y = ranNum() % (input.rows / 2), 
		four_X = ranNum() % (input.cols / 2), four_Y = ranNum() % (input.rows / 2);

	// Input Quadilateral or Image plane coordinates
	Point2f inputQuad[4];
	// Output Quadilateral or World plane coordinates
	Point2f outputQuad[4];

	// Lambda Matrix
	Mat lambda(2, 4, CV_32FC1);
	//Input and Output Image;
	Mat output;

	//Load the image
	// Set the lambda matrix the same type and size as input
	lambda = Mat::zeros(input.rows, input.cols, input.type());

	// The 4 points that select quadilateral on the input , from top-left in clockwise order
	// These four pts are the sides of the rect box used as input 
	/*
	왼쪽에서 볼 경우
	오른쪽에서 볼 경우
	위에서 볼 경우
	*/
	inputQuad[0] = Point2f(-one_X, -one_Y);
	inputQuad[1] = Point2f(input.cols + two_X, -two_Y);
	inputQuad[2] = Point2f(input.cols + three_X, input.rows + three_Y);
	inputQuad[3] = Point2f(-four_X, input.rows + four_Y);
	// The 4 points where the mapping is to be done , from top-left in clockwise order
	outputQuad[0] = Point2f(0, 0);
	outputQuad[1] = Point2f(input.cols - 1, 0);
	outputQuad[2] = Point2f(input.cols - 1, input.rows - 1);
	outputQuad[3] = Point2f(0, input.rows - 1);

	// Get the Perspective Transform Matrix i.e. lambda 
	//lambda = getPerspectiveTransform(inputQuad, outputQuad);
	lambda = getPerspectiveTransform(inputQuad, outputQuad);
	//cout << lambda;
	lambda.at<double>(0, 0);

	int xmin = 999999, ymin = 9999999, xmax = 0, ymax = 0;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			int rx = 0, ry = 0;
			rx = int((lambda.at<double>(0, 0)*x[i] + lambda.at<double>(0, 1)*y[j] + lambda.at<double>(0, 2)) /
				(lambda.at<double>(2, 0)*x[i] + lambda.at<double>(2, 1)*y[j] + lambda.at<double>(2, 2)));
			ry = int((lambda.at<double>(1, 0)*x[i] + lambda.at<double>(1, 1)*y[j] + lambda.at<double>(1, 2)) /
				(lambda.at<double>(2, 0)*x[i] + lambda.at<double>(2, 1)*y[j] + lambda.at<double>(2, 2)));
			if (rx > xmax) xmax = int(rx);
			if (rx < xmin) xmin = int(rx);
			if (ry > ymax) ymax = int(ry);
			if (ry < ymin) ymin = int(ry);
		}
	}
	result_x[0] = xmin;
	result_x[1] = xmax;
	result_y[0] = ymin;
	result_y[1] = ymax;
	//cout << rx << " " << ry << endl;
	// Apply the Perspective Transform just found to the src image
	warpPerspective(input, output, lambda, output.size());

	//Display input and output
	//imshow("Input", input);
	//imshow("Output", output);

	//waitKey(0);
	return output;
}
