#include "Watermark_Processing.h"
#include "Processing.h"
#include "Watermark.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

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

struct RGB {
	uchar blue;
	uchar green;
	uchar red;
};

struct RGB_Float {
	float blue;
	float green;
	float red;
};
int  Img_Size_Type = 0;

char data_red_path[100];
char data_green_path[100];
char data_blue_path[100];

cv::Mat Image_In;
cv::Mat Image_Out;

TCHAR*  Open_in;
TCHAR*  Open_out;

//using namespace cv;
using namespace std;

extern void Image_Processing_New(cv::Mat* image);

void Change_Transparency_Color_FF(RGB_Float& shadow_pxl, RGB& pxl, float contour_back, float contour_font);
void Change_Transparency_Color_00(RGB_Float& shadow_pxl, RGB& pxl);


void Watermark_Processing(cv::Mat *image, float *contour_back, float *contour_font) {
	int width = image->cols;
	int height = image->rows;
	int row_offset = (height - 640) / 2;
	int col_offset = (width - 800) / 2;
	volatile int shadow_row = 0;
	volatile int shadow_col = 0;
	RGB_Float shadow_pxl;

	int row_start = LOGO_ROW_START + row_offset;
	int window_height = LOGO_WINDOW_HEIGHT;
	int col_start = LOGO_COL_START + col_offset;
	int window_width = 170;
	int row_end = row_start + window_height;
	int col_end = col_start + window_width;
	int shadow_row_offset = 0;
	int shadow_col_offset = 0;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			//if ((shadow_pxl.red != 0) || (shadow_pxl.green != 0) || (shadow_pxl.blue != 0)) {
			//	pxl.blue = 0;
			//	pxl.green = 0;
			//	pxl.blue = 0;

			//}
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[0], contour_font[0]);
		}

	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = 570 + col_offset;
	window_width = 170;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = 570 - LOGO_COL_START;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[0], contour_font[0]);
		}


	//for (int row = 395; row < 537; row++)
	//	for (int col = 60; col < (60 + 110); col++) {
	//		shadow_pxl.red = shadow[row - 395][col - 60][0];
	//		shadow_pxl.green = shadow[row - 395][col - 60][1];
	//		shadow_pxl.blue = shadow[row - 395][col - 60][2];
	//		RGB& pxl = image->ptr<RGB>(row + row_offset)[col];
	//		Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[1], contour_font[1]);
	//	}

	//for (int row = 395; row < 537; row++)
	//	for (int col = (740 - 110); col < 740; col++) {
	//		shadow_pxl.red = shadow[row - 395][col - 60][0];
	//		shadow_pxl.green = shadow[row - 395][col - 60][1];
	//		shadow_pxl.blue = shadow[row - 395][col - 60][2];
	//		RGB& pxl = image->ptr<RGB>(row + row_offset)[col];
	//		Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[2], contour_font[2]);
	//	}


	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = 230 + col_offset;
	window_width = 340;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = 230 - LOGO_COL_START;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[3], contour_font[3]);
		}

	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset;
	window_width = LOGO_WINDOW_WIDTH;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = 0;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = red_white[shadow_row][shadow_col];
			shadow_pxl.green = green_white[shadow_row][shadow_col];
			shadow_pxl.blue = blue_white[shadow_row][shadow_col];
			RGB& pxl = image->ptr<RGB>(row)[col];
			Change_Transparency_Color_00(shadow_pxl, pxl);
		}

	//Dilation(0, 0);
}


void Watermark_Processing_1200_960(cv::Mat *image, float *contour_back, float *contour_font) {
	int width = image->cols;
	int height = image->rows;
	int row_offset = (height - 640) / 2;
	int col_offset = (width - 800) / 2;
	volatile int shadow_row = 0;
	volatile int shadow_col = 0;
	RGB_Float shadow_pxl;


	int row_start = LOGO_ROW_START + row_offset;
	int window_height = LOGO_WINDOW_HEIGHT;
	int col_start = LOGO_COL_START + col_offset;
	int window_width = LOGO_WINDOW_WIDTH;
	int row_end = row_start + window_height;
	int col_end = col_start + window_width;
	int shadow_row_offset = 0;
	int shadow_col_offset = 0;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = red_white[shadow_row][shadow_col];
			shadow_pxl.green = green_white[shadow_row][shadow_col];
			shadow_pxl.blue = blue_white[shadow_row][shadow_col];
			RGB& pxl = image->ptr<RGB>(row)[col];
			Change_Transparency_Color_00(shadow_pxl, pxl);
		}


	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset;
	window_width = (LOGO_WINDOW_WIDTH / 2) - 30;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = 0;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			//if ((shadow_pxl.red != 0) || (shadow_pxl.green != 0) || (shadow_pxl.blue != 0)) {
				//pxl.blue = 0;
				//pxl.green = 0;
				//pxl.blue = 0;

			//}
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[0], contour_font[0]);
		}


	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset + (LOGO_WINDOW_WIDTH / 2) + 30;
	window_width = (LOGO_WINDOW_WIDTH / 2) - 30;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = (LOGO_WINDOW_WIDTH / 2) + 30;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			//if ((shadow_pxl.red != 0) || (shadow_pxl.green != 0) || (shadow_pxl.blue != 0)) {
				//pxl.blue = 0;
				//pxl.green = 0;
				//pxl.blue = 0;

			//}
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[0], contour_font[0]);
		}


	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset + (LOGO_WINDOW_WIDTH / 2) - 30;
	window_width = 60;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = (LOGO_WINDOW_WIDTH / 2) - 30;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = shadow[shadow_row][shadow_col][0];
			shadow_pxl.green = shadow[shadow_row][shadow_col][1];
			shadow_pxl.blue = shadow[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			//if ((shadow_pxl.red != 0) || (shadow_pxl.green != 0) || (shadow_pxl.blue != 0)) {
				//pxl.blue = 0;
				//pxl.green = 0;
				//pxl.blue = 0;

			//}
			Change_Transparency_Color_FF(shadow_pxl, pxl, contour_back[1], contour_font[1]);
		}


	row_start = LOGO_ROW_START + row_offset;
	window_height = LOGO_WINDOW_HEIGHT;
	col_start = LOGO_COL_START + col_offset;
	window_width = LOGO_WINDOW_WIDTH;
	row_end = row_start + window_height;
	col_end = col_start + window_width;
	shadow_row_offset = 0;
	shadow_col_offset = 0;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			shadow_row = row - row_start + shadow_row_offset;
			shadow_col = col - col_start + shadow_col_offset;
			shadow_pxl.red = artifact[shadow_row][shadow_col][0];
			shadow_pxl.green = artifact[shadow_row][shadow_col][1];
			shadow_pxl.blue = artifact[shadow_row][shadow_col][2];
			RGB& pxl = image->ptr<RGB>(row)[col];
			Change_Transparency_Color_FF(shadow_pxl, pxl, 0.0, 266);
		}


	//Dilation(0, 0);
}


void Change_Transparency_Color_00(RGB_Float& shadow_pxl, RGB& pxl) {
	float A, R, F, B;
	if (shadow_pxl.red != 1) {
		A = (float)shadow_pxl.red;
		R = (float)pxl.red;
		F = learn_white_front[0];
		B = (R - F * A) / (1 - A);
		if (B < 0.0) B = 0;
		if (B > 255.0) B = 255;
		pxl.red = (uchar)std::round(B);
	}

	if (shadow_pxl.green != 1) {
		A = (float)shadow_pxl.green;
		R = (float)pxl.green;
		F = learn_white_front[1];
		B = (R - F * A) / (1 - A);
		if (B < 0.0) B = 0;
		if (B > 255.0) B = 255;
		pxl.green = (uchar)std::round(B);
	}

	if (shadow_pxl.blue != 1) {
		A = (float)shadow_pxl.blue;
		R = (float)pxl.blue;
		F = learn_white_front[2];
		B = (R - F * A) / (1 - A);
		if (B < 0.0) B = 0;
		if (B > 255.0) B = 255;
		pxl.blue = (uchar)std::round(B);
	}
}



void Change_Transparency_Color_FF(RGB_Float& shadow_pxl, RGB& pxl, float contour_back, float contour_font) {
	float A, R, F, B;
	if (shadow_pxl.red != 1) {
		A = (float)shadow_pxl.red;
		R = (float)pxl.red;
		F = contour_font;
		B = (R - F * A) / (1 - A);
		if (B < 0) B = 0;
		if (B > 255) B = 255;
		pxl.red = (uchar)std::round(B);
	}

	if (shadow_pxl.green != 1) {
		A = (float)shadow_pxl.green;
		R = (float)pxl.green;
		F = contour_font;
		B = (R - F * A) / (1 - A);
		if (B < 0) B = 0;
		if (B > 255) B = 255;
		pxl.green = (uchar)std::round(B);
	}

	if (shadow_pxl.blue != 1) {
		A = (float)shadow_pxl.blue;
		R = (float)pxl.blue;
		F = contour_font;
		B = (R - F * A) / (1 - A);
		if (B < 0) B = 0;
		if (B > 255) B = 255;
		pxl.blue = (uchar)std::round(B);
	}
}



void Watermark_Text_Processing(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name) {
	cv::Mat imageLogoText;
	imageLogoText = imread(cv::samples::findFile(name), cv::IMREAD_COLOR); // Read the file
	int width = imageLogoText.cols;
	int height = imageLogoText.rows;


	//RGB& pxl = image->ptr<RGB>(0)[0];
	RGB_Float shadow_pxl;
	int gown = 0; int right = 0;
	int left = width;
	int up = height;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			if ((pxl.red < 225) || (pxl.green < 225) || (pxl.blue < 225)) {
				if (col > right) right = col;
				if (col < left) left = col;
				if (row > gown) gown = row;
				if (row < up) up = row;
			}
		}
	printf("right: %d\n", right);
	printf("left: %d\n", left);
	printf("up: %d\n", up);
	printf("gown: %d\n", gown);

	float A, R, F, B;

	up = row_start;
	gown = row_end;
	left = col_start;
	right = col_end;
	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			B = learn_white_back[0];
			F = learn_white_front[0];
			R = (float)pxl.red;
			if (R < 224.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}

			red_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[1];
			F = learn_white_front[1];
			R = (float)pxl.green;
			if (R < 224.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			green_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[2];
			F = learn_white_front[2];
			R = (float)pxl.blue;
			if (R < 224.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			blue_white[row - up][col - left + offset_left] = A;

		}

	//R = B * (1 - A) + F * A
	//R = B + (F - B)*A
	//B — яркость фонового пикселя;
	//F — яркость накладываемого пикселя;
	//A[0..1] — непрозрачность накладываемого пикселя;
	//R ― результат.


	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			shadow_pxl.red = red_white[row - up][col - left + offset_left];
			shadow_pxl.green = green_white[row - up][col - left + offset_left];
			shadow_pxl.blue = blue_white[row - up][col - left + offset_left];
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			Change_Transparency_Color_00(shadow_pxl, pxl);
		}




	for (int i = left; i <= right; i++) {
		RGB& pxl1 = imageLogoText.ptr<RGB>(up)[i];
		pxl1.red = 120;
		pxl1.green = 120;
		pxl1.blue = 120;
		RGB& pxl2 = imageLogoText.ptr<RGB>(gown)[i];
		pxl2.red = 120;
		pxl2.green = 120;
		pxl2.blue = 120;
	}

	for (int i = up; i < gown; i++) {
		RGB& pxl3 = imageLogoText.ptr<RGB>(i)[left];
		pxl3.red = 120;
		pxl3.green = 120;
		pxl3.blue = 120;
		RGB& pxl4 = imageLogoText.ptr<RGB>(i)[right];
		pxl4.red = 120;
		pxl4.green = 120;
		pxl4.blue = 120;
	}
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("Display window", imageLogoText);        // Show our image inside it.

}
void Watermark_Text_Processing_1200_960(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name) {
	cv::Mat imageLogoText;
	imageLogoText = imread(cv::samples::findFile(name), cv::IMREAD_COLOR); // Read the file
	int width = imageLogoText.cols;
	int height = imageLogoText.rows;


	//RGB& pxl = image->ptr<RGB>(0)[0];
	RGB_Float shadow_pxl;
	int gown = 0; int right = 0;
	int left = width;
	int up = height;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			if ((pxl.red < 255) || (pxl.green < 255) || (pxl.blue < 255)) {
				if (col > right) right = col;
				if (col < left) left = col;
				if (row > gown) gown = row;
				if (row < up) up = row;
			}
		}
	printf("right: %d\n", right);
	printf("left: %d\n", left);
	printf("up: %d\n", up);
	printf("gown: %d\n", gown);

	float A, R, F, B;

	up = row_start;
	gown = row_end;
	left = col_start;
	right = col_end;
	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			B = learn_white_back[0];
			F = learn_white_front[0];
			R = (float)pxl.red;
			if (R < learn_white_back[0]) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}

			red_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[1];
			F = learn_white_front[1];
			R = (float)pxl.green;
			if (R < learn_white_back[1]) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			green_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[2];
			F = learn_white_front[2];
			R = (float)pxl.blue;
			if (R < learn_white_back[2]) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			blue_white[row - up][col - left + offset_left] = A;

		}

	//R = B * (1 - A) + F * A
	//R = B + (F - B)*A
	//B — яркость фонового пикселя;
	//F — яркость накладываемого пикселя;
	//A[0..1] — непрозрачность накладываемого пикселя;
	//R ― результат.


	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			shadow_pxl.red = red_white[row - up][col - left + offset_left];
			shadow_pxl.green = green_white[row - up][col - left + offset_left];
			shadow_pxl.blue = blue_white[row - up][col - left + offset_left];
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			Change_Transparency_Color_00(shadow_pxl, pxl);
		}




	for (int i = left; i <= right; i++) {
		RGB& pxl1 = imageLogoText.ptr<RGB>(up)[i];
		pxl1.red = 120;
		pxl1.green = 120;
		pxl1.blue = 120;
		RGB& pxl2 = imageLogoText.ptr<RGB>(gown)[i];
		pxl2.red = 120;
		pxl2.green = 120;
		pxl2.blue = 120;
	}

	for (int i = up; i < gown; i++) {
		RGB& pxl3 = imageLogoText.ptr<RGB>(i)[left];
		pxl3.red = 120;
		pxl3.green = 120;
		pxl3.blue = 120;
		RGB& pxl4 = imageLogoText.ptr<RGB>(i)[right];
		pxl4.red = 120;
		pxl4.green = 120;
		pxl4.blue = 120;
	}
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("Display window", imageLogoText);        // Show our image inside it.

}

void Watermark_Text_Processing_1500x1200(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name) {
	cv::Mat imageLogoText;
	imageLogoText = imread(cv::samples::findFile(name), cv::IMREAD_COLOR); // Read the file
	int width = imageLogoText.cols;
	int height = imageLogoText.rows;


	//RGB& pxl = image->ptr<RGB>(0)[0];
	RGB_Float shadow_pxl;
	int gown = 0; int right = 0;
	int left = width;
	int up = height;
	for (int row = row_start; row < row_end; row++)
		for (int col = col_start; col < col_end; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			if ((pxl.red < 255) || (pxl.green < 255) || (pxl.blue < 255)) {
				if (col > right) right = col;
				if (col < left) left = col;
				if (row > gown) gown = row;
				if (row < up) up = row;
			}
		}
	printf("right: %d\n", right);
	printf("left: %d\n", left);
	printf("up: %d\n", up);
	printf("gown: %d\n", gown);

	float A, R, F, B;

	up = row_start;
	gown = row_end;
	left = col_start;
	right = col_end;
	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			B = learn_white_back[0];
			F = learn_white_front[0];
			R = (float)pxl.red;
			if (R < 254.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}

			red_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[1];
			F = learn_white_front[1];
			R = (float)pxl.green;
			if (R < 254.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			green_white[row - up][col - left + offset_left] = A;

			B = learn_white_back[2];
			F = learn_white_front[2];
			R = (float)pxl.blue;
			if (R < 254.0) {
				A = (R - B) / (F - B);
			}
			else {
				A = 0.0;
			}
			blue_white[row - up][col - left + offset_left] = A;

		}

	//R = B * (1 - A) + F * A
	//R = B + (F - B)*A
	//B — яркость фонового пикселя;
	//F — яркость накладываемого пикселя;
	//A[0..1] — непрозрачность накладываемого пикселя;
	//R ― результат.


	for (int row = up; row < gown; row++)
		for (int col = left; col < right; col++) {
			shadow_pxl.red = red_white[row - up][col - left + offset_left];
			shadow_pxl.green = green_white[row - up][col - left + offset_left];
			shadow_pxl.blue = blue_white[row - up][col - left + offset_left];
			RGB& pxl = imageLogoText.ptr<RGB>(row)[col];
			Change_Transparency_Color_00(shadow_pxl, pxl);
		}




	for (int i = left; i <= right; i++) {
		RGB& pxl1 = imageLogoText.ptr<RGB>(up)[i];
		pxl1.red = 120;
		pxl1.green = 120;
		pxl1.blue = 120;
		RGB& pxl2 = imageLogoText.ptr<RGB>(gown)[i];
		pxl2.red = 120;
		pxl2.green = 120;
		pxl2.blue = 120;
	}

	for (int i = up; i < gown; i++) {
		RGB& pxl3 = imageLogoText.ptr<RGB>(i)[left];
		pxl3.red = 120;
		pxl3.green = 120;
		pxl3.blue = 120;
		RGB& pxl4 = imageLogoText.ptr<RGB>(i)[right];
		pxl4.red = 120;
		pxl4.green = 120;
		pxl4.blue = 120;
	}
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	cv::imshow("Display window", imageLogoText);        // Show our image inside it.

}
void Check_Size_White(char *size, char *data_red, char *data_green, char *data_blue) {
	if (strcmp(size, "800_800") == 0) {
		strcpy(data_red , "Data\\4.txt");
		strcpy(data_green , "Data\\5.txt");
		strcpy(data_blue , "Data\\6.txt");
	}
	else if (strcmp(size, "1200_960") == 0) {
		strcpy(data_red , "Data\\4_1200_960.dat");
		strcpy(data_green , "Data\\5_1200_960.dat");
		strcpy(data_blue , "Data\\6_1200_960.dat");
	}
	else if (strcmp(size, "Test") == 0) {
		strcpy(data_red, "Data\\4_Test.dat");
		strcpy(data_green, "Data\\5_Test.dat");
		strcpy(data_blue, "Data\\6_Test.dat");
		Img_Size_Type = IMG_SIZE_800_800;
	}
	else {
		sprintf(data_red, "Data\\4_%s.dat", size);
		sprintf(data_green, "Data\\5_%s.dat", size);
		sprintf(data_blue, "Data\\6_%s.dat", size);
	}
}
void Check_Size(char *size, char *data_red, char *data_green, char *data_blue) {
	if (strcmp(size, "800_800") == 0) {
		strcpy(data_red , "Data\\1.dat");
		strcpy(data_green , "Data\\2.dat");
		strcpy(data_blue , "Data\\3.dat");
		Img_Size_Type = IMG_SIZE_800_800;
	}
	else if (strcmp(size, "1200_960") == 0) {
		strcpy(data_red , "Data\\1_1200_960.dat");
		strcpy(data_green , "Data\\2_1200_960.dat");
		strcpy(data_blue , "Data\\3_1200_960.dat");
		Img_Size_Type = IMG_SIZE_960_1200;
	}
	else if (strcmp(size, "Test") == 0) {
		strcpy(data_red, "Data\\1_Test.dat");
		strcpy(data_green, "Data\\2_Test.dat");
		strcpy(data_blue, "Data\\3_Test.dat");
		Img_Size_Type = IMG_SIZE_800_800;
	}
	else {
		sprintf(data_red, "Data\\1_%s.dat", size);
		sprintf(data_green, "Data\\2_%s.dat", size);
		sprintf(data_blue, "Data\\3_%s.dat", size);
	}
}

void Check_Size_Artifact(char *size, char *data_red, char *data_green, char *data_blue) {
	if (strcmp(size, "800_800") == 0) {
		//strcpy(data_red, "Data\\1.dat");
		//strcpy(data_green, "Data\\2.dat");
		//strcpy(data_blue, "Data\\3.dat");
	}
	else if (strcmp(size, "1200_960") == 0) {
		strcpy(data_red, "Data\\1_art_1200_960.dat");
		strcpy(data_green, "Data\\2_art_1200_960.dat");
		strcpy(data_blue, "Data\\3_art_1200_960.dat");
	}
	else {
		sprintf(data_red, "Data\\1_art_%s.dat", size);
		sprintf(data_green, "Data\\2_art_%s.dat", size);
		sprintf(data_blue, "Data\\3_art_%s.dat", size);
	}
}
void Save_White(char *size) {
	//float test;
	std::ofstream offile;
	Check_Size_White(size, data_red_path, data_green_path, data_blue_path);


	//test = 0.0;
	offile.open(data_red_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << red_white[row][col] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();


	//test = 0.0;
	offile.open(data_green_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << green_white[row][col] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();

	//test = 0.0;
	offile.open(data_blue_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << blue_white[row][col] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();
}

void Read_White(char *size) {
	int row, col;
	float temp_f;
	//float test = 0;
	std::ifstream infile;
	std::string line;
	row = 0; col = 0;
	Check_Size_White(size, data_red_path, data_green_path, data_blue_path);

	//test = 0.0;
	infile.open(data_red_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 4.dat!", TEXT("Error"), MB_OK);
		return;
	}
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		red_white[row][col] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	//test = 0.0;
	infile.open(data_green_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 5.dat!", TEXT("Error"), MB_OK);
		return;
	}
	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		green_white[row][col] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	//test = 0.0;
	infile.open(data_blue_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 6.dat!", TEXT("Error"), MB_OK);
		return;
	}
	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		blue_white[row][col] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

}

void Save_Artifact(char *size) {
	Check_Size_Artifact(size, data_red_path, data_green_path, data_blue_path);

	std::ofstream offile;

	offile.open(data_red_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << artifact[row][col][0] << endl;
		}
	offile.close();

	offile.open(data_green_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << artifact[row][col][1] << endl;
		}
	offile.close();

	offile.open(data_blue_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << artifact[row][col][2] << endl;
		}
	offile.close();
}

void Read_Artifact(char *size) {
	int row, col;
	float temp_f;
	std::ifstream infile;
	std::string line;
	row = 0; col = 0;
	Check_Size_Artifact(size, data_red_path, data_green_path, data_blue_path);
	infile.open(data_red_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 1.dat!", TEXT("Error"), MB_OK);
		return;
	}
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		artifact[row][col][0] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	infile.open(data_green_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 2.dat!", TEXT("Error"), MB_OK);
		return;
	}

	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		artifact[row][col][1] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	infile.open(data_blue_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 3.dat!", TEXT("Error"), MB_OK);
		return;
	}

	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		artifact[row][col][2] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

}

void Save_Shadow(char *size) {
	Check_Size(size, data_red_path, data_green_path, data_blue_path);

	std::ofstream offile;
	//float test = 0;
	offile.open(data_red_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << shadow[row][col][0] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();

	//test = 0;
	offile.open(data_green_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << shadow[row][col][1] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();

	//test = 0;
	offile.open(data_blue_path);
	for (int row = 0; row < LOGO_HEIGHT; row++)
		for (int col = 0; col < LOGO_WIDTH; col++) {
			offile << shadow[row][col][2] << endl;
			//offile << test << endl;
			//test += 1.0;
		}
	offile.close();
}

void Read_Shadow(char *size) {
	int row, col;
	float temp_f;
	std::ifstream infile;
	std::string line;
	row = 0; col = 0;
	//float test = 0.0;
	Check_Size(size, data_red_path, data_green_path, data_blue_path);
	infile.open(data_red_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 1.dat!", TEXT("Error"), MB_OK);
		return;
	}
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		shadow[row][col][0] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	infile.open(data_green_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 2.dat!", TEXT("Error"), MB_OK);
		return;
	}
	//test = 0.0;
	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		shadow[row][col][1] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

	infile.open(data_blue_path);
	if (!infile.good()) {
		MessageBox(NULL, L"Not found 3.dat!", TEXT("Error"), MB_OK);
		return;
	}
	//test = 0.0;
	row = 0; col = 0;
	while (getline(infile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		temp_f = (float)atof(line.c_str());
		//if (temp_f != test) {
		//	printf("ERROR red float! File float: %f, Array float: %f, row: %d, col: %d\n", temp_f, red_white[row][col], row, col);
		//}
		//test += 1.0;
		shadow[row][col][2] = temp_f;
		col++;
		if (col == LOGO_WIDTH) {
			row++;
			col = 0;
		}
		if (row == LOGO_HEIGHT) {
			row = 0;
		}
	}
	infile.close();

}


void DisplayErrorBox(LPTSTR lpszFunction);

int Image_Processing(TCHAR* path_in, TCHAR* path_out, float *contour_back, float *contour_font)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir_In[MAX_PATH];
	TCHAR szDir_Out[MAX_PATH];
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	int width = 0;
	int height = 0;
	int img_type_size = 0;

	vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
	compression_params.push_back(compression);
	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.

	StringCchLength(path_in, MAX_PATH, &length_of_arg);

	if (length_of_arg > (MAX_PATH - 3))
	{
		printf("\nDirectory path is too long.\n");
		return (-1);
	}

	StringCchLength(path_out, MAX_PATH, &length_of_arg);

	if (length_of_arg > (MAX_PATH - 3))
	{
		printf("\nDirectory path is too long.\n");
		return (-1);
	}

	//_tprintf(TEXT("\nTarget directory is %s\n\n"), argv[1]);

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.

	StringCchCopy(szDir_In, MAX_PATH, path_in);
	StringCchCat(szDir_In, MAX_PATH, TEXT("\\*"));

	//StringCchCopy(szDir_Out, MAX_PATH, path_out);
	//StringCchCat(szDir_Out, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir_In, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
		return dwError;
	}

	// List all the files in the directory with some info about them.

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("  %ls   <DIR>\n", ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			printf("  %ls   %ld bytes\n", ffd.cFileName, filesize.QuadPart);

			cv::Mat image;
			StringCchCopy(szDir, MAX_PATH, path_in);
			StringCchCat(szDir, MAX_PATH, TEXT("\\"));
			StringCchCat(szDir, MAX_PATH, ffd.cFileName);
			wstring wfname_in(szDir);
			image = cv::imread(cv::samples::findFile(string(wfname_in.begin(), wfname_in.end())), cv::IMREAD_COLOR); // Read the file
			if (image.empty())                      // Check for invalid input
			{
				cout << "Could not open or find the image" << std::endl;
				continue;
			}

			width = image.cols;
			height = image.rows;

			extern int  Img_Size_Type;
			if ((width == 800) && (height == 800)) {
				Img_Size_Type = IMG_SIZE_800_800;
				//continue;
			}
			else if ((width == 800) && (height == 640)) {
				Img_Size_Type = IMG_SIZE_640_800;
				//continue;
			}
			else if ((width == 1200) && (height == 960)) {
				Img_Size_Type = IMG_SIZE_960_1200;
				//continue;
			}
			else if ((width == 1500) && (height == 1200)) {
				Img_Size_Type = IMG_SIZE_1500_1200;
				//continue;
			}
			else {
				continue;
			}

			
				if ((Img_Size_Type == IMG_SIZE_800_800) || (Img_Size_Type == IMG_SIZE_640_800)) {
					if (Img_Size_Type != img_type_size) {
						img_type_size = Img_Size_Type;
						Read_Settings_Fast("800_800");
						Read_White("800_800");
						Read_Shadow("800_800");
					}
					Watermark_Processing(&image, contour_back, contour_font);
				}
				else if (Img_Size_Type == IMG_SIZE_960_1200) {
					if (Img_Size_Type != img_type_size) {
						img_type_size = Img_Size_Type;
						Read_Settings_Fast("1200_960");
						Read_White("1200_960");
						Read_Shadow("1200_960");
					}
					Watermark_Processing_1200_960(&image, contour_back, contour_font);
				}
				else if (Img_Size_Type == IMG_SIZE_1500_1200) {
					if (Img_Size_Type != img_type_size) {
						char imgsize[40];
						sprintf_s(imgsize, "%d_%d", image.cols, image.rows);
						Read_Logo_Text_Array(imgsize);
						Read_Logo_Shadow_Array(imgsize);
					}
					Image_Processing_New(&image);
				}
			
			StringCchCopy(szDir_Out, MAX_PATH, path_out);
			StringCchCat(szDir_Out, MAX_PATH, TEXT("\\"));
			StringCchCat(szDir_Out, MAX_PATH, ffd.cFileName);
			wstring wfname_out(szDir_Out);
			cv::putText(image, "TEST PHOTOS", cv::Point(image.rows / 2 - 120, image.cols / 2 - 120), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(10, 10, 255), 6, CV_AA);
			cv::imwrite(string(wfname_out.begin(), wfname_out.end()), image, compression_params);
		}

		if (exit_image_processing)
		{
			exit_image_processing = false;
			break;
		}



	} while (FindNextFile(hFind, &ffd) != 0);

	//dwError = GetLastError();
	//if (dwError != ERROR_NO_MORE_FILES)
	//{
	//	DisplayErrorBox(TEXT("FindFirstFile"));
	//}

	FindClose(hFind);
	return dwError;
}


void DisplayErrorBox(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and clean up

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}


void Read_Settings_Fast(char *str)
{
	std::ifstream infile;
	std::string line;
	const char *name;
	if (strcmp(str, "1200_960") == 0) {
		name = "Data\\Settings_1200_960.dat";
	}
	else if (strcmp(str, "800_800") == 0) {
		name = "Data\\Settings_800_800.dat";
	}
	else {
		return;
	}

	infile.open(name);
	if (!infile.good()) {
		//MessageBox("Not found 1.dat!");
		return;
	}
	for (int i = 0; i < 4; i++) {
		getline(infile, line);
		learn_contour_back[i] = (float)atof(line.c_str());
		getline(infile, line);
		learn_contour_front[i] = (float)atof(line.c_str());
		getline(infile, line);
		process_contour_back[i] = (float)atof(line.c_str());
		getline(infile, line);
		process_contour_front[i] = (float)atof(line.c_str());
	}

	for (int i = 0; i < 3; i++) {
		getline(infile, line);
		learn_white_back[i] = (float)atof(line.c_str());
		getline(infile, line);
		learn_white_front[i] = (float)atof(line.c_str());
		getline(infile, line);
		process_white_back[i] = (float)atof(line.c_str());
		getline(infile, line);
		process_white_front[i] = (float)atof(line.c_str());
	}

	getline(infile, line);
	compression = atoi(line.c_str());
}
