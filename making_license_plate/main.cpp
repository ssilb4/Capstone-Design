#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
const int max_num = 10;
const int max_char = 33;
const string type = ".jpg";
const string plate = "plate";
const string character[33] = { "beo", "bo", "bu", "da", "deo", "do",  
"du", "eo", "ga", "geo", "go", "gu", "heo", "jeo", "jo", "ju",
"ma", "meo", "mo", "mu", "na", "neo", "no", "nu", "o", "ra", "reo",
"ro", "ru", "seo", "so", "su", "u" };
const string number[10] = { "zero", "one", "two", "three", "four", "five", 
"six", "seven", "eight", "nine" };

const int char_x[7] = { 127,285,443,716,874,1033,1192 };
const int char_y = 40;
int main()
{
	string directory = "../no1/";
	string result_directory = "../no1_result/";
	string temp_plate = directory + plate + type;
	string result_name = result_directory;
	string temp_char = directory + character[0] + type;
	string temp_num = directory + number[0] + type;
	
	cv::Mat image = cv::imread(temp_plate);
	cv::Mat logo_char = cv::imread(temp_char);
	cv::Mat logo_num = cv::imread(temp_num);

	for (int a = 0; a < max_num; a++) {
		temp_num = directory + number[a] + type;
		logo_num = cv::imread(temp_num);
		cv::Mat imageROI = image(cv::Rect(char_x[0], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
		for (int b = 0; b < max_num; b++) {
			temp_num = directory + number[b] + type;
			logo_num = cv::imread(temp_num);
			imageROI = image(cv::Rect(char_x[1], char_y, logo_num.cols, logo_num.rows));
			cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
			for (int c = 0; c < max_char; c++) {
				temp_char = directory + character[c] + type;
				logo_char = cv::imread(temp_char);
				imageROI = image(cv::Rect(char_x[2], char_y, logo_char.cols, logo_char.rows));
				cv::addWeighted(imageROI, 0.0, logo_char, 1.0, 0., imageROI);
				for (int d = 0; d < max_num; d++) {
					temp_num = directory + number[d] + type;
					logo_num = cv::imread(temp_num);
					imageROI = image(cv::Rect(char_x[3], char_y, logo_num.cols, logo_num.rows));
					cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
					for (int e = 0; e < max_num; e++) {
						temp_num = directory + number[e] + type;
						logo_num = cv::imread(temp_num);
						imageROI = image(cv::Rect(char_x[4], char_y, logo_num.cols, logo_num.rows));
						cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
						for (int f = 0; f < max_num; f++) {
							temp_num = directory + number[f] + type;
							logo_num = cv::imread(temp_num);
							imageROI = image(cv::Rect(char_x[5], char_y, logo_num.cols, logo_num.rows));
							cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
							for (int g = 0; g < max_num; g++) {
								temp_num = directory + number[g] + type;
								logo_num = cv::imread(temp_num);
								imageROI = image(cv::Rect(char_x[6], char_y, logo_num.cols, logo_num.rows));
								// 영상 ROI 정의
								// 사각형으로 시작x 시작y 끝x 끝y
								cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
								// 영상에 로고 붙이기
								// imageROI = 1.0*imageROI + 0.3*logo + 0
								result_name = result_directory + number[a] + number[b] + character[c] + number[d] + number[e] + number[f] + number[g] + type;
								cv::imshow("aaa", image);
								cout << result_name << endl;
								//cv::imwrite("abc.jpg", image);
								const char * imagefile = result_name.c_str();
								cvSaveImage(imagefile, &(IplImage(image)));
								cout << a << b << c << d << e << f << g << "번째" << endl;
							
							}
						}
					}
				}
			}
		}
	}

	cv::waitKey(0);

	return 0;
}
