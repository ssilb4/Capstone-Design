#include "makexml.h"


Mat alpha(Mat foreground, Mat background, Mat alpha, int location[]) {
	// Read the images

	Mat ouImage = Mat::zeros(foreground.size(), foreground.type());


	bitwise_and(alpha, foreground, foreground, noArray());

	Mat imageROI = background(cv::Rect(location[0], location[1], alpha.cols, alpha.rows));
	//255 - alpha
	bitwise_not(alpha, alpha, noArray());

	bitwise_and(alpha, imageROI, imageROI, noArray());
	add(foreground, imageROI, imageROI);
	//background.convertTo(background, CV_8UC3, 255);

	// Add the masked foreground and background.

	// Display image
	//imshow("alpha blended image", background );
	//waitKey(0);
	return background;
}
