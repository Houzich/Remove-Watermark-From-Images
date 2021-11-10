#include "Watermark.h"
#include "Learning.h"
#include "Processing.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;

extern LogoArr	shadow_arr;
extern LogoArr	text_arr;
LogoArr	logo_arr;
struct RGBColor {
	uchar color[3];
};

cv::Mat image_for_click;

extern void Shadow_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr);
extern void Text_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr);
extern void Save_Logo_Array(LogoArr arr, char* type, char* imgsize);
extern void Read_Settings(String^ size, LogoLearning* dt1, LogoLearning* dt2, int* step1, int* step2);
void CvImageMouseCallBackFunc(int event, int x, int y, int flags, void* userdata);


void Region_Shadow_Learning(cv::Mat* image, LogoLearning* dt) {
	float A, R, F[3], B[3];

	for (int i = 0; i < 3; i++) {
		F[i] = dt->color_front[i];
		B[i] = dt->color_back[i];
	}

	for (int img_row = dt->img_row_start, logo_row = dt->window_row_start; img_row < dt->img_row_start + dt->window_height; img_row++, logo_row++)
		for (int img_col = dt->img_col_start, logo_col = dt->window_col_start; img_col < dt->img_col_start + dt->window_width; img_col++, logo_col++) {
			RGBColor& pxl = image->ptr<RGBColor>(img_row)[img_col];

			A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
			logo_arr[logo_row][logo_col][0] = A;

			A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
			logo_arr[logo_row][logo_col][1] = A;

			A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
			logo_arr[logo_row][logo_col][2] = A;
		}
}

void Region_Text_Learning(cv::Mat* image, LogoLearning* dt) {
	float A, R, F[3], B[3];

	for (int i = 0; i < 3; i++) {
		F[i] = dt->color_front[i];
		B[i] = dt->color_back[i];
	}

	for (int img_row = dt->img_row_start, logo_row = dt->window_row_start; img_row < dt->img_row_start + dt->window_height; img_row++, logo_row++)
		for (int img_col = dt->img_col_start, logo_col = dt->window_col_start; img_col < dt->img_col_start + dt->window_width; img_col++, logo_col++) {
			RGBColor& pxl = image->ptr<RGBColor>(img_row)[img_col];

			A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
			if (pxl.color[0] == B[0]) A = 0;
			logo_arr[logo_row][logo_col][0] = A;

			A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
			if (pxl.color[1] == B[1]) A = 0;
			logo_arr[logo_row][logo_col][1] = A;

			A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
			if (pxl.color[2] == B[2]) A = 0;
			logo_arr[logo_row][logo_col][2] = A;


			//A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
			//if (pxl.color[2] == B[2]) A = 0;
			//logo_arr[logo_row][logo_col][2] = A;
			//logo_arr[logo_row][logo_col][1] = A;
			//logo_arr[logo_row][logo_col][0] = A;

		}
}

void Shadow_Learning(LogoLearning *dt, int step) {

	if (step == 0) return;
	cv::Mat image;
	for (size_t i = 0; i < step; i++)
	{
		image = cv::imread(cv::samples::findFile(dt[i].imageName), cv::IMREAD_COLOR); // Read the file
		//define coordinates on image
		int img_row = (image.rows / 2) - 5;
		int img_col = (image.cols / 2) - (LOGO_WINDOW_WIDTH / 2);
		dt[i].img_row_start = img_row + dt[i].window_row_start;
		dt[i].img_col_start = img_col + dt[i].window_col_start;
		
		Region_Shadow_Learning(&image, &dt[i]);

		//draw rectangle
		cv::Rect rect(dt[i].img_col_start, dt[i].img_row_start, dt[i].window_width, dt[i].window_height);
		cv::rectangle(image, rect, cv::Scalar(0, 255, 0));

		string name = "Shadow Learning part " + std::to_string(i);
		cv::namedWindow(name, cv::WINDOW_NORMAL);
		image_for_click = image;
		//________________________________________________
		cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
		cv::setMouseCallback(name, CvImageMouseCallBackFunc, &image_for_click);
		//________________________________________________
		cv::imshow(name, image_for_click);		
	}

	//LogoLearning dt1[10];
	//LogoLearning dt2[10];
	//int step1, step2;
	//Read_Settings(,dt1, dt2, &step1, &step2);

	image = cv::imread(cv::samples::findFile(dt[0].imageName), cv::IMREAD_COLOR); // Read the file
	Shadow_Processing(&image, &dt[0], 1, logo_arr);
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test_shadow_1.jpg", image);
	//image = cv::imread(cv::samples::findFile(dt[1].imageName), cv::IMREAD_COLOR); // Read the file
	//Shadow_Processing(&image, &dt1[1], 2, logo_arr);
	//cv::imwrite("D:\\ABITANT\\img_out\\test_shadow_2.jpg", image);
	//image = cv::imread(cv::samples::findFile(dt[2].imageName), cv::IMREAD_COLOR); // Read the file
	//Shadow_Processing(&image, &dt1[2], 1, logo_arr);
	//cv::imwrite("D:\\ABITANT\\img_out\\test_shadow_3.jpg", image);


	//This need save logo arr
	char imgsize[100];
	sprintf_s(imgsize, "%dx%d", image.cols, image.rows);
	Save_Logo_Array(logo_arr, "shadow", imgsize);
}
//learning the text contour
void Text_Learning(String^ size, LogoLearning* dt, int step) {

	if (step == 0) return;
	cv::Mat image;
	for (size_t i = 0; i < step; i++)
	{
		image = cv::imread(cv::samples::findFile(dt[i].imageName), cv::IMREAD_COLOR); // Read the file
		//read array and settings
		LogoLearning dt1[10];
		LogoLearning dt2[10];
		int step1, step2;
		char imgsize[40];
		sprintf_s(imgsize, "%dx%d", image.cols, image.rows);
		Read_Logo_Text_Array(imgsize);
		Read_Logo_Shadow_Array(imgsize);	
		Read_Settings(size, dt1, dt2, &step1, &step2);
		Shadow_Processing(&image, dt1, step1, shadow_arr);
																					  
		//define coordinates on image
		int img_row = (image.rows / 2) - 5;
		int img_col = (image.cols / 2) - (LOGO_WINDOW_WIDTH / 2);
		dt[i].img_row_start = img_row + dt[i].window_row_start;
		dt[i].img_col_start = img_col + dt[i].window_col_start;

		Region_Text_Learning(&image, &dt[i]);

		////draw rectangle
		//cv::Rect rect(dt[i].img_col_start, dt[i].img_row_start, dt[i].window_width, dt[i].window_height);
		//cv::rectangle(image, rect, cv::Scalar(0, 255, 0));

		//cv::Mat croppedImage = image(rect);
		//cv::resize(croppedImage, croppedImage, cv::Size(), 4, 4);

		//string name = "Text Learning part " + std::to_string(i);
		//cv::namedWindow(name, cv::WINDOW_NORMAL);
		////image_for_click = croppedImage;
		//image_for_click = image;
		////________________________________________________
		//cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
		//cv::setMouseCallback(name, CvImageMouseCallBackFunc, &image_for_click);
		////________________________________________________
		//cv::imshow(name, image_for_click);
	}
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test_text_1.jpg", image);
	Text_Processing(&image, dt, step, logo_arr);
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test_text_2.jpg", image);

	//This need save logo arr
	char imgsize[100];
	sprintf_s(imgsize, "%dx%d", image.cols, image.rows);
	Save_Logo_Array(logo_arr, "text", imgsize);
}


void CvImageMouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		cv::Mat *image = (cv::Mat*)userdata;

		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		printf("Pixel %d %d: %d, %d, %d\n",
			x, y,
			(int)(*image).at<cv::Vec3b>(y, x)[0],
			(int)(*image).at<cv::Vec3b>(y, x)[1],
			(int)(*image).at<cv::Vec3b>(y, x)[2]);

	}
}