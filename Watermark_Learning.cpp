#include "Watermark_Processing.h"
#include "Watermark_Learning.h"
#include "Watermark.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <conio.h>

//#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <stdint.h>

#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
//#pragma comment(lib, "User32.lib")

using namespace std;

using namespace System;
//using namespace System::Windows::Forms;
int erosion_elem = 2;
int erosion_size = 2;
int dilation_elem = 1;
int dilation_size = 20;
int const max_elem = 2;
int const max_kernel_size = 21;

cv::Mat image_learning;
struct RGBColor {
	uchar color[3];
};




//using namespace cv;
using namespace std;

void ArtifactCallBackFunc(int event, int x, int y, int flags, void* userdata);
void Shodow_Learning(cv::Mat *image, int row_start, int row_offset, int window_height, int col_start, int col_offset, int window_width, float *contour_back, float *contour_font) {
int width = image->cols;
int height = image->rows;
int height_offset = (height - 640) / 2;


float A, R, F[3], B[3];

for (int i = 0; i < 3; i++) {
	F[i] = contour_font[i];
	B[i] = contour_back[i];
}
//int start_row = row_start + height_offset;
int start_row = row_start;
for (int row = start_row; row < start_row + window_height; row++)
	for (int col = col_start; col < col_start + window_width; col++) {
		int shadow_row = row - start_row + row_offset;
		int shadow_col = col - col_start + col_offset;

		RGBColor& pxl = image->ptr<RGBColor>(row)[col];

		A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
		shadow[shadow_row][shadow_col][0] = A;
		//shadow[shadow_row][shadow_col][0] = 0.5;

		A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
		shadow[shadow_row][shadow_col][1] = A;
		//shadow[shadow_row][shadow_col][1] = 0.5;

		A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
		shadow[shadow_row][shadow_col][2] = A;
		//shadow[shadow_row][shadow_col][2] = 0.5;
	}
}


void Learning_Processing(const char *str) {
	string imageName;
	int size_num = 0;
	if (strcmp(str, "1200_960") == 0) {
		size_num = 2;
		Learning_Processing_1200x960(learn_contour_back, learn_contour_front);
		imageName ="D:\\ABITANT\\test\\1200x960_3.jpg";
		//imageName ="D:\\ABITANT\\test\\1200x960_2.jpg";
		//imageName = "Data_Learning\\logo_10.jpg";
		//imageName = "D:\\ABITANT\\white_1.jpg";
	}
	else if (strcmp(str, "800_800") == 0) {
		size_num = 1;
		Learning_Processing_800x800(learn_contour_back, learn_contour_front);
		imageName = "D:\\ABITANT\\img_in\\komod_scarlet_splendour_designs_2019_88_secrets_sideboard_verde_rose_large.jpg";
	}
	else {
		return;
	}


	Image_In = cv::imread(cv::samples::findFile(imageName), cv::IMREAD_COLOR); // Read the file
	if (Image_In.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return;
	}
	if (size_num == 1) {
		Watermark_Processing(&Image_In, process_contour_back, process_contour_front);
	}
	else if (size_num == 2) {
		Watermark_Processing_1200_960(&Image_In, process_contour_back, process_contour_front);
	}

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", Image_In);                // Show our image inside it.

	string imageName_Out("D:\\ABITANT\\img_out\\test.jpg"); // by default
	vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
	compression_params.push_back(compression);
	cv::imwrite(imageName_Out, Image_In, compression_params);
}

void Learning_Processing_1200x960(float *f_back, float *f_font) {

	cv::Mat imageLogoShadow;
	float contour_back[3] = { 0.0,0.0,0.0 };
	float contour_font[3] = { 0.0,0.0,0.0 };
	int row_start = LOGO_ROW_START;
	int window_height = LOGO_WINDOW_HEIGHT;
	int col_start = LOGO_COL_START;
	int window_width = LOGO_WINDOW_WIDTH;
	int row_offset = 0;
	int col_offset = 0;
	int height = 0;
	int width = 0;
	int height_offset = 0;
	int row_offset_logo = 0;
	int col_offset_logo = 0;
	string imageLogoShadowName1("Data_Learning\\logo_10.jpg");
	imageLogoShadow = cv::imread(cv::samples::findFile(imageLogoShadowName1), cv::IMREAD_COLOR); // Read the file
	width = imageLogoShadow.cols;
	height = imageLogoShadow.rows;
	row_offset = (height - 640) / 2;
	col_offset = (width - 800) / 2;
	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset;
	window_width = (LOGO_WINDOW_WIDTH / 2) - 30;
	row_offset_logo = 0;
	col_offset_logo = 0;
	RGBColor& pxl1 = imageLogoShadow.ptr<RGBColor>(LOGO_ROW_START - 10)[LOGO_COL_START - 10];
	printf("Pixsel back: %d, %d, %d\n", pxl1.color[0], pxl1.color[1], pxl1.color[2]);
	for (int i = 0; i < 3; i++) contour_back[i] = f_back[0];
	for (int i = 0; i < 3; i++) contour_font[i] = f_font[0];

	Shodow_Learning(&imageLogoShadow, row_start, row_offset_logo, window_height, col_start, col_offset_logo, window_width, contour_back, contour_font);
	
	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset + (LOGO_WINDOW_WIDTH / 2) + 30;
	window_width = (LOGO_WINDOW_WIDTH / 2) - 30;
	row_offset_logo = 0;
	col_offset_logo = (LOGO_WINDOW_WIDTH / 2) + 30;
	for (int i = 0; i < 3; i++) contour_back[i] = f_back[0];
	for (int i = 0; i < 3; i++) contour_font[i] = f_font[0];

	Shodow_Learning(&imageLogoShadow, row_start, row_offset_logo, window_height, col_start, col_offset_logo, window_width, contour_back, contour_font);

	imageLogoShadowName1 ="Data_Learning\\logo_13.jpg";
	imageLogoShadow = cv::imread(cv::samples::findFile(imageLogoShadowName1), cv::IMREAD_COLOR); // Read the file
	width = imageLogoShadow.cols;
	height = imageLogoShadow.rows;
	row_offset = (height - 640) / 2;
	col_offset = (width - 800) / 2;
	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset + (LOGO_WINDOW_WIDTH / 2) - 30;
	window_width = 60;
	row_offset_logo = 0;
	col_offset_logo = (LOGO_WINDOW_WIDTH / 2) - 30;
	for (int i = 0; i < 3; i++) contour_back[i] = f_back[1];
	for (int i = 0; i < 3; i++) contour_font[i] = f_font[1];

	Shodow_Learning(&imageLogoShadow, row_start, row_offset_logo, window_height, col_start, col_offset_logo, window_width, contour_back, contour_font);

	Save_Shadow("1200_960");
}

void Learning_Processing_800x800(float *f_back, float *f_font) {

	cv::Mat imageLogoShadow;
	float contour_back[3] = { 0.0,0.0,0.0 };
	float contour_font[3] = { 0.0,0.0,0.0 };
	int row_start = LOGO_ROW_START;
	int window_height = LOGO_WINDOW_HEIGHT;
	int col_start = LOGO_COL_START;
	int window_width = LOGO_WINDOW_WIDTH;
	int row_offset = 0;
	int col_offset = 0;
	int height = 0;
	int height_offset = 0;
	string imageLogoShadowName1("Data_Learning\\logo_1.jpg");
	imageLogoShadow = cv::imread(cv::samples::findFile(imageLogoShadowName1), cv::IMREAD_COLOR); // Read the file

	row_start = LOGO_ROW_START;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START;
	window_width = LOGO_WINDOW_WIDTH;
	row_offset = 0;
	col_offset = 0;
	RGBColor& pxl1 = imageLogoShadow.ptr<RGBColor>(385)[400];
	printf("Pixsel back: %d, %d, %d", pxl1.color[0], pxl1.color[1], pxl1.color[2]);
	for (int i = 0; i < 3; i++) contour_back[i] = f_back[0];
	for (int i = 0; i < 3; i++) contour_font[i] = f_font[0];

	Shodow_Learning(&imageLogoShadow, row_start, row_offset, window_height, col_start, col_offset, window_width, contour_back, contour_font);

	//string imageLogoShadowName2("Data_Learning\\logo_2.jpg");
	//imageLogoShadow = cv::imread(cv::samples::findFile(imageLogoShadowName2), cv::IMREAD_COLOR); // Read the file
	//height = imageLogoShadow.rows;
	//height_offset = (height - 640) / 2;
	//row_start = LOGO_ROW_START;
	//window_height = LOGO_WINDOW_HEIGHT;
	//col_start = LOGO_COL_START;
	//window_width = 110;
	//row_offset = 0;
	//col_offset = 0;
	//RGB& pxl2 = imageLogoShadow.ptr<RGB>(LOGO_ROW_START + height_offset)[60];

	//for (int i = 0; i < 3; i++) contour_back[i] = f_back[1];
	//for (int i = 0; i < 3; i++) contour_font[i] = f_font[1];
	//Shodow_Learning(&imageLogoShadow, row_start, row_offset, window_height, col_start, col_offset, window_width, contour_back, contour_font);

	//row_start = LOGO_ROW_START;
	//window_height = LOGO_WINDOW_HEIGHT;
	//col_start = 630;
	//window_width = 110;
	//row_offset = 0;
	//col_offset = col_start - 60;
	//RGB& pxl3 = imageLogoShadow.ptr<RGB>(LOGO_ROW_START + height_offset)[740];

	//for (int i = 0; i < 3; i++) contour_back[i] = f_back[2];
	//for (int i = 0; i < 3; i++) contour_font[i] = f_font[2];
	//Shodow_Learning(&imageLogoShadow, row_start, row_offset, window_height, col_start, col_offset, window_width, contour_back, contour_font);

	string imageLogoShadowName3("Data_Learning\\logo_6.jpg");
	imageLogoShadow = cv::imread(cv::samples::findFile(imageLogoShadowName3), cv::IMREAD_COLOR); // Read the file
	height = imageLogoShadow.rows;
	height_offset = (height - 640) / 2;
	row_start = LOGO_ROW_START;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = 230;
	window_width = 340;
	row_offset = 0;
	col_offset = col_start - 60;
	//pxl = imageLogoShadow.ptr<RGB>(LOGO_ROW_START + height_offset)[60];

	for (int i = 0; i < 3; i++) contour_back[i] = f_back[3];
	for (int i = 0; i < 3; i++) contour_font[i] = f_font[3];
	Shodow_Learning(&imageLogoShadow, row_start, row_offset, window_height, col_start, col_offset, window_width, contour_back, contour_font);

	
	Save_Shadow("800_800");
}

/**  @function Erosion  */
void Erosion(int, void*)
{
	int erosion_type;
	if (erosion_elem == 0) { erosion_type = cv::MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = cv::MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

	cv::Mat element = cv::getStructuringElement(erosion_type,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	/// Apply the erosion operation
	cv::erode(Image_In, Image_Out, element);
	cv::imshow("Erosion Demo", Image_Out);
}

/** @function Dilation */
void Dilation(int, void*)
{
	int dilation_type;
	if (dilation_elem == 0) { dilation_type = cv::MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = cv::MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

	cv::Mat element = cv::getStructuringElement(dilation_type,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));
	/// Apply the dilation operation
	cv::dilate(Image_In, Image_Out, element);
	cv::imshow("Dilation Demo", Image_Out);
}


void Learning_Artifact_1200_960(int limit_1, int limit_2, int limit_3, int color_offset) {
	string imageName;
	for (int row = 0; row < 142; row++)
		for (int col = 0; col < 680; col++) {
			artifact[row][col][0] = 0;
			artifact[row][col][1] = 0;
			artifact[row][col][2] = 0;
		}


	float A, R, F[3], B[3];

	for (int i = 0; i < 3; i++) {
		F[i] = 266;
		B[i] = 0;
	}

	imageName = "D:\\ABITANT\\test\\artifact_1.jpg";
	image_learning = cv::imread(cv::samples::findFile(imageName)); // Read the file
	int width = image_learning.cols;
	int height = image_learning.rows;
	int row_offset = (height - 640) / 2;
	int col_offset = (width - 800) / 2;
	int row_start = LOGO_ROW_START + row_offset;
	int window_height = LOGO_WINDOW_HEIGHT;
	int col_start = LOGO_COL_START + col_offset;
	int window_width = 150;
	int logo_row_offset = 0;
	int logo_col_offset = 0;

	for (int i = 0; i < 3; i++) {
		B[i] = 149 - color_offset;
	}
	for (int row = row_start; row < row_start + window_height; row++)
		for (int col = col_start; col < col_start + window_width; col++) {
				int shadow_row = row - row_start + logo_row_offset;
				int shadow_col = col - col_start + logo_col_offset;
				RGBColor& pxl = image_learning.ptr<RGBColor>(row)[col];
				//if ((pxl.color[0] < limit_1) && (pxl.color[1] < limit_2) && (pxl.color[2] < limit_3))
				if ((pxl.color[0] < 149) && (pxl.color[1] < 149) && (pxl.color[2] < 149))
				{
					pxl.color[0] = 0; pxl.color[1] = 0; pxl.color[2] = 0;
				}
				else {
					A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
					artifact[shadow_row][shadow_col][0] = A;
					A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
					artifact[shadow_row][shadow_col][1] = A;
					A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
					artifact[shadow_row][shadow_col][2] = A;
				}
		}

	col_start = LOGO_COL_START + col_offset + 150;
	window_width = 112;
	logo_col_offset = 150;
	for (int i = 0; i < 3; i++) {
		B[i] = 142 - (color_offset - 2);
	}
	for (int row = row_start; row < row_start + window_height; row++)
		for (int col = col_start; col < col_start + window_width; col++) {
			int shadow_row = row - row_start + logo_row_offset;
			int shadow_col = col - col_start + logo_col_offset;
			RGBColor& pxl = image_learning.ptr<RGBColor>(row)[col];
			//if ((pxl.color[0] < limit_1) && (pxl.color[1] < limit_2) && (pxl.color[2] < limit_3))
			if ((pxl.color[0] < 142) && (pxl.color[1] < 142) && (pxl.color[2] < 142))
			{
				pxl.color[0] = 0; pxl.color[1] = 0; pxl.color[2] = 0;
			}
			else {
				A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
				artifact[shadow_row][shadow_col][0] = A;
				A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
				artifact[shadow_row][shadow_col][1] = A;
				A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
				artifact[shadow_row][shadow_col][2] = A;
			}
		}


	col_start = LOGO_COL_START + col_offset + 280;
	window_width = 150;
	logo_col_offset = 280;
	for (int i = 0; i < 3; i++) {
		B[i] = 137 - color_offset;
	}
	for (int row = row_start; row < row_start + window_height; row++)
		for (int col = col_start; col < col_start + window_width; col++) {

			int shadow_row = row - row_start + logo_row_offset;
			int shadow_col = col - col_start + logo_col_offset;
			RGBColor& pxl = image_learning.ptr<RGBColor>(row)[col];
			//if ((pxl.color[0] < limit_1) && (pxl.color[1] < limit_2) && (pxl.color[2] < limit_3))
			if ((pxl.color[0] < 137) && (pxl.color[1] < 137) && (pxl.color[2] < 137))
			{
				pxl.color[0] = 0; pxl.color[1] = 0; pxl.color[2] = 0;
			}
			else {
				A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
				artifact[shadow_row][shadow_col][0] = A;
				A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
				artifact[shadow_row][shadow_col][1] = A;
				A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
				artifact[shadow_row][shadow_col][2] = A;
			}
		}

	col_start = LOGO_COL_START + col_offset + 430;
	window_width = 150;
	logo_col_offset = 430;
	for (int i = 0; i < 3; i++) {
		B[i] = 134 - color_offset;
	}
	for (int row = row_start; row < row_start + window_height; row++)
		for (int col = col_start; col < col_start + window_width; col++) {

			int shadow_row = row - row_start + logo_row_offset;
			int shadow_col = col - col_start + logo_col_offset;
			RGBColor& pxl = image_learning.ptr<RGBColor>(row)[col];
			//if ((pxl.color[0] < limit_1) && (pxl.color[1] < limit_2) && (pxl.color[2] < limit_3))
			if ((pxl.color[0] < 134) && (pxl.color[1] < 134) && (pxl.color[2] < 134))
			{
				pxl.color[0] = 0; pxl.color[1] = 0; pxl.color[2] = 0;
			}
			else {
				A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
				artifact[shadow_row][shadow_col][0] = A;
				A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
				artifact[shadow_row][shadow_col][1] = A;
				A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
				artifact[shadow_row][shadow_col][2] = A;
			}
		}
	col_start = LOGO_COL_START + col_offset + 580;
	window_width = 100;
	logo_col_offset = 580;
	for (int i = 0; i < 3; i++) {
		B[i] = 137 - (color_offset + 5);
	}
	for (int row = row_start; row < row_start + window_height; row++)
		for (int col = col_start; col < col_start + window_width; col++) {

			int shadow_row = row - row_start + logo_row_offset;
			int shadow_col = col - col_start + logo_col_offset;
			RGBColor& pxl = image_learning.ptr<RGBColor>(row)[col];
			//if ((pxl.color[0] < limit_1) && (pxl.color[1] < limit_2) && (pxl.color[2] < limit_3))
			if ((pxl.color[0] < 137) && (pxl.color[1] < 137) && (pxl.color[2] < 137))
			{
				pxl.color[0] = 0; pxl.color[1] = 0; pxl.color[2] = 0;
			}
			else {
				A = (pxl.color[0] - B[0]) / (F[0] - B[0]);
				artifact[shadow_row][shadow_col][0] = A;
				A = (pxl.color[1] - B[1]) / (F[1] - B[1]);
				artifact[shadow_row][shadow_col][1] = A;
				A = (pxl.color[2] - B[2]) / (F[2] - B[2]);
				artifact[shadow_row][shadow_col][2] = A;
			}
		}


	cv::namedWindow("Artifact display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	//set the callback function for any mouse event
	cv::setMouseCallback("Artifact display window", ArtifactCallBackFunc, NULL);
	imshow("Artifact display window", image_learning);                // Show our image inside it.

	//string imageName_Out("D:\\ABITANT\\img_out\\test_artifact.jpg"); // by default
	//vector<int> compression_params;
	//compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
	//compression_params.push_back(compression);
	//cv::imwrite(imageName_Out, image, compression_params);
	Save_Artifact("1200_960");
}

void ArtifactCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		printf("Pixel %d %d: %d, %d, %d\n",
			x, y,
			(int)(image_learning).at<cv::Vec3b>(y, x)[0],
			(int)(image_learning).at<cv::Vec3b>(y, x)[1],
			(int)(image_learning).at<cv::Vec3b>(y, x)[2]);

	}
	//else if (event == cv::EVENT_RBUTTONDOWN)
	//{
	//	cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	//}
	//else if (event == cv::EVENT_MBUTTONDOWN)
	//{
	//	cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	//}
	//else if (event == cv::EVENT_MOUSEMOVE)
	//{
	//	cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	//}
}