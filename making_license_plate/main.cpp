#include "makexml.h"

const int max_num = 1000;	//만들 개수
const int min_num = 0;		//고정
const int car_count = 10;	//고정
const int back_count = 10;	//고정
const int num_count = 10;	//고정
const int char_count = 33;	//고정
const string imgtype = ".jpg";
const string txttype = ".txt";
const string plate = "plate";
const string car = "car";
const string background = "back";
const string mask = "_mask";
const string character[33] = { "beo", "bo", "bu", "da", "deo", "do",
"du", "eo", "ga", "geo", "go", "gu", "heo", "jeo", "jo", "ju",
"ma", "meo", "mo", "mu", "na", "neo", "no", "nu", "o", "ra", "reo",
"ro", "ru", "seo", "so", "su", "u" };
const string number[10] = { "0", "1", "2", "3", "4", "5",
"6", "7", "8", "9" };

const int char_x[7] = { 127,285,443,716,874,1033,1192 };
const int char_y = 40;
cv::Size plate_size = cv::Size(172, 37);
int plate_x[2] = { 264,305 };
int plate_y[2] = { 264,305 };
int result_x[2] = { 264,305 };
int result_y[2] = { 264,305 };

void file_read(string name, string type) {
	ifstream ifile;

	char line[200]; // 한 줄씩 읽어서 임시로 저장할 공간
	string file = name + type;
	ifile.open(file);  // 파일 열기

	if (ifile.is_open())
	{
		int count = 0;
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			if (count % 2 == 0) {
				plate_x[0] = atoi(line);
				plate_x[1] = plate_x[0] + 172;
			}
			else {
				plate_y[0] = atoi(line);
				plate_y[1] = plate_y[0] + 37;
			}
			count++;
		}
	}

	ifile.close(); // 파일 닫기

	return;
}
int main()
{
	string directory = "../no1/";
	string result_directory = "../no1_result/";
	string temp_plate = directory + plate + imgtype;
	string result_name = result_directory;
	string temp_char = directory + character[0] + imgtype;
	string temp_num = directory + number[0] + imgtype;


	cv::Mat image = cv::imread(temp_plate);
	cv::Mat logo_char = cv::imread(temp_char);
	cv::Mat logo_num = cv::imread(temp_num);

	//랜덤
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 ranNum(seed);

	for (int index = min_num; index < max_num; index++) {
		//background
		int back_index = ranNum() % back_count;
		string temp_back = directory + background + '/' + background + number[back_index];
		cv::Mat background_image = cv::imread(temp_back + imgtype);

		//car
		int car_index = ranNum() % car_count;
		string temp_car = directory + car + '/' + car + number[car_index];
		cv::Mat car_image = cv::imread(temp_car + imgtype);
		file_read(temp_car, txttype);

		//first number
		int a = ranNum() % num_count;
		temp_num = directory + number[a] + imgtype;
		logo_num = cv::imread(temp_num);
		cv::Mat imageROI = image(cv::Rect(char_x[0], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);

		//second number
		int b = ranNum() % num_count;
		temp_num = directory + number[b] + imgtype;
		logo_num = cv::imread(temp_num);
		imageROI = image(cv::Rect(char_x[1], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);

		//character
		int c = ranNum() % char_count;
		temp_num = directory + number[c] + imgtype;
		logo_char = cv::imread(temp_char);
		imageROI = image(cv::Rect(char_x[2], char_y, logo_char.cols, logo_char.rows));
		cv::addWeighted(imageROI, 0.0, logo_char, 1.0, 0., imageROI);

		//third number
		int d = ranNum() % num_count;
		temp_num = directory + number[d] + imgtype;
		logo_num = cv::imread(temp_num);
		imageROI = image(cv::Rect(char_x[3], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);

		//fourth number
		int e = ranNum() % num_count;
		temp_num = directory + number[e] + imgtype;
		logo_num = cv::imread(temp_num);
		imageROI = image(cv::Rect(char_x[4], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);

		//fifth number
		int f = ranNum() % num_count;
		temp_num = directory + number[f] + imgtype;
		logo_num = cv::imread(temp_num);
		imageROI = image(cv::Rect(char_x[5], char_y, logo_num.cols, logo_num.rows));
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);

		//sixth number
		int g = ranNum() % num_count;
		temp_num = directory + number[g] + imgtype;
		logo_num = cv::imread(temp_num);
		imageROI = image(cv::Rect(char_x[6], char_y, logo_num.cols, logo_num.rows));
		// 영상 ROI 정의
		// 사각형으로 시작x 시작y 끝x 끝y
		cv::addWeighted(imageROI, 0.0, logo_num, 1.0, 0., imageROI);
		// 영상에 로고 붙이기
		// imageROI = 1.0*imageROI + 0.3*logo + 0
		result_name = number[a] + number[b] + character[c] + number[d] + number[e] + number[f] + number[g] + car + char(car_index + '0') + background + char(back_index + '0'); //car number back number
																																												//cv::imshow("aaa", image);
		cout << result_name << endl;
		//cv::imwrite("abc.jpg", image);

		//mask
		cv::Mat mask_image = cv::imread(temp_car + mask + imgtype);

		cv::Mat dst1;
		cv::resize(image, dst1, plate_size, 0, 0);
		imageROI = car_image(cv::Rect(plate_x[0], plate_y[0], dst1.cols, dst1.rows));
		cv::addWeighted(imageROI, 0.0, dst1, 1.0, 0., imageROI);

		cv::Mat dst3;
		cv::Size back_size = cv::Size(background_image.cols, background_image.rows);
		cv::resize(background_image, dst3, back_size, 0, 0);
		imageROI = dst3(cv::Rect(0, 0, background_image.cols, background_image.rows));
		cv::addWeighted(imageROI, 0.0, dst3, 1.0, 0., imageROI);

		/*
		cv::Mat dst2;
		cv::Size car_size = cv::Size(car_image.cols, car_image.rows);
		cv::resize(car_image, dst2, car_size, 0, 0);
		imageROI = dst3(cv::Rect(0, 0, dst2.cols, dst2.rows));
		cv::addWeighted(imageROI, 0.0, dst2, 1.0, 0., imageROI);
		*/


		int car_location[2] = {ranNum() % (background_image.cols - car_image.cols), ranNum() % (background_image.rows - car_image.rows)};

		dst3 = alpha(car_image, dst3, mask_image, car_location);
		dst3 = gaussian(dst3);
		
		plate_x[0] += car_location[0];
		plate_x[1] += car_location[0];
		plate_y[0] += car_location[1];
		plate_y[1] += car_location[1];
		
		dst3 = argument(dst3, plate_x, plate_y, result_x, result_y);

		makexml(result_directory, result_name, imgtype, "1", background_image.cols, background_image.rows, result_x[0], result_x[1], result_y[0], result_y[1]);
		result_name = result_directory + result_name + imgtype;
		const char * imagefile = result_name.c_str();
		//cvSaveImage(imagefile, &(IplImage(image)));
		cvSaveImage(imagefile, &(IplImage(dst3)));
		cout << a << b << c << d << e << f << g << "번째" << endl;
		cvDestroyWindow(imagefile);
		//cvReleaseImage(&(IplImage(background_image)));
	}

	cv::waitKey(0);

	return 0;
}
