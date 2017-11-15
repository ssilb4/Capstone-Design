#include "makexml.h"

Mat argument(Mat input, int x[], int y[])
{
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
	//오른쪽 -, 왼쪽 +, 아래가 - 위가 +
	int minX = -300, maxX = 300, minY = -150, maxY = 150;
	inputQuad[0] = Point2f(minX, minY);
	inputQuad[1] = Point2f(input.cols + maxX, -maxY);
	inputQuad[2] = Point2f(input.cols + maxX, input.rows + minY);
	inputQuad[3] = Point2f(minX, input.rows + maxY);
	// The 4 points where the mapping is to be done , from top-left in clockwise order
	outputQuad[0] = Point2f(0, 0);
	outputQuad[1] = Point2f(input.cols - 1, 0);
	outputQuad[2] = Point2f(input.cols - 1, input.rows - 1);
	outputQuad[3] = Point2f(0, input.rows - 1);

	// Get the Perspective Transform Matrix i.e. lambda 
	lambda = getPerspectiveTransform(inputQuad, outputQuad);
	cout << lambda;
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
	x[0] = xmin;
	x[1] = xmax;
	y[0] = ymin;
	y[1] = ymax;
	//cout << rx << " " << ry << endl;
	// Apply the Perspective Transform just found to the src image
	warpPerspective(input, output, lambda, output.size());

	//Display input and output
	//imshow("Input", input);
	//imshow("Output", output);

	//waitKey(0);
	return output;
}