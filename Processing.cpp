#include "Processing.h"
#include "Learning.h"
#include "Watermark.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;
//using namespace Watermark;
using namespace System;

LogoArr	shadow_arr;
LogoArr	text_arr;
extern void Read_Settings(System::String^ size, LogoLearning* dt1, LogoLearning* dt2, int* step1, int* step2);
void Shadow_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr);
void Text_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr);


struct RGB {
	uchar color[3];
};

struct Coeff {
	float c[3];
};


void Modify_Pixel(Coeff& coeff, RGB& pxl, LogoLearning* dt) {
	float A, R, F, B;

	for (size_t i = 0; i < 3; i++)
	{
		if (coeff.c[i] != 1) {
			A = (float)coeff.c[i];
			R = (float)pxl.color[i];
			F = dt->color_front[i];
			B = (R - F * A) / (1 - A);
			if (B < 0) B = 0.0;
			if (B > 255) B = 255.0;
			//pxl.color[i] = (uchar)std::round(B);
			pxl.color[i] = (uchar)B;
		}
	}
}


void Image_Processing_New(cv::Mat* image, System::String^ size){
	LogoLearning dt1[10];
	LogoLearning dt2[10];
	int step1, step2;
	Read_Settings(size, dt1, dt2, &step1, &step2);
	Shadow_Processing(image, dt1, step1, shadow_arr);
	Text_Processing(image, dt2, step2, text_arr);
}

void Shadow_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr) {
	Coeff coeff_pxl;
	if (step == 0) return;
	for (size_t i = 0; i < step; i++)
	{
		//define coordinates on image
		int img_row = (image->rows / 2) - 5;
		int img_col = (image->cols / 2) - (LOGO_WIDTH / 2);
		//coordinates on image
		int img_row_start = img_row + dt[i].window_row_start;
		int img_col_start = img_col + dt[i].window_col_start;
		int img_row_end = img_row_start + dt[i].window_height;
		int img_col_end = img_col_start + dt[i].window_width;
		for (int row = img_row_start; row < img_row_end; row++)
			for (int col = img_col_start; col < img_col_end; col++) {
				int logo_row = row - img_row_start + dt[i].window_row_start;
				int logo_col = col - img_col_start + dt[i].window_col_start;
				coeff_pxl.c[0] = logo_arr[logo_row][logo_col][0];
				coeff_pxl.c[1] = logo_arr[logo_row][logo_col][1];
				coeff_pxl.c[2] = logo_arr[logo_row][logo_col][2];
				RGB& pxl = image->ptr<RGB>(row)[col];
				Modify_Pixel(coeff_pxl, pxl, &dt[i]);
			}


	}

	//string name = "Image after Shadow Processing";
	//cv::namedWindow(name, CV_WINDOW_NORMAL);
	//cv::imshow(name, *image);
}

void Text_Processing(cv::Mat* image, LogoLearning* dt, int step, LogoArr logo_arr) {
	Coeff coeff_pxl;
	if (step == 0) return;
	for (size_t i = 0; i < step; i++)
	{
		//define coordinates on image
		int img_row = (image->rows / 2) - 5;
		int img_col = (image->cols / 2) - (LOGO_WIDTH / 2);
		//coordinates on image
		int img_row_start = img_row + dt[i].window_row_start;
		int img_col_start = img_col + dt[i].window_col_start;
		int img_row_end = img_row_start + dt[i].window_height;
		int img_col_end = img_col_start + dt[i].window_width;
		for (int row = img_row_start; row < img_row_end; row++)
			for (int col = img_col_start; col < img_col_end; col++) {
				int logo_row = row - img_row_start + dt[i].window_row_start;
				int logo_col = col - img_col_start + dt[i].window_col_start;
				coeff_pxl.c[0] = logo_arr[logo_row][logo_col][0];
				coeff_pxl.c[1] = logo_arr[logo_row][logo_col][1];
				coeff_pxl.c[2] = logo_arr[logo_row][logo_col][2];
				RGB& pxl = image->ptr<RGB>(row)[col];
				Modify_Pixel(coeff_pxl, pxl, &dt[i]);
			}


	}

	//string name = "Image after Text Processing";
	//cv::namedWindow(name, CV_WINDOW_NORMAL);
	//cv::imshow(name, *image);
}



/*
type = shadow
or
type = text
*/
void Save_Logo_Array(LogoArr arr, char* type, char* imgsize) {
	//float test;
	std::ofstream offile;
	char path[200];
	sprintf(path, "Data\\%s_%s.dat", type, imgsize);

	offile.open(path);
	for (int i = 0; i < 3; i++)
		for (int row = 0; row < LOGO_HEIGHT; row++)
			for (int col = 0; col < LOGO_WIDTH; col++) {
				offile << arr[row][col][i] << endl;
			}
	offile.close();
}


void Read_Logo_Shadow_Array(char* imgsize) {
	std::ifstream infile;
	std::string line;
	float temp_f;
	char path[100];
	sprintf_s(path, "Data\\shadow_%s.dat", imgsize);
	//sprintf_s(path, "Data\\shadow_800x640.dat", imgsize);

	infile.open(path);
	for (int i = 0; i < 3; i++)
		for (int row = 0; row < LOGO_HEIGHT; row++)
			for (int col = 0; col < LOGO_WIDTH; col++) {
				getline(infile, line);
				temp_f = (float)atof(line.c_str());
				shadow_arr[row][col][i] = temp_f;
			}
	infile.close();
}

void Read_Logo_Text_Array(char* imgsize) {
	std::ifstream infile;
	std::string line;
	float temp_f;
	char path[100];
	sprintf_s(path, "Data\\text_%s.dat", imgsize);
	//sprintf_s(path, "Data\\text_800x640.dat", imgsize);

	infile.open(path);
	for (int i = 0; i < 3; i++)
		for (int row = 0; row < LOGO_HEIGHT; row++)
			for (int col = 0; col < LOGO_WIDTH; col++) {
				getline(infile, line);
				temp_f = (float)atof(line.c_str());
				text_arr[row][col][i] = temp_f;
			}
	infile.close();
}

char old_imgsize[40];
int Processing_Folder(TCHAR* path_in, TCHAR* path_out)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir_In[MAX_PATH];
	TCHAR szDir_Out[MAX_PATH];
	TCHAR szDir[MAX_PATH];
	static TCHAR Dirs[1000][MAX_PATH];



	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	int width = 0;
	int height = 0;
	int img_type_size = 0;

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.
	size_t length_of_arg;
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

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.
	StringCchCopy(szDir_In, MAX_PATH, path_in);
	StringCchCat(szDir_In, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir_In, &ffd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		printf("Error FindFirstFile!!!\n");
		return  (-1);
	}


	//StringCchCopy(Dirs[0], MAX_PATH, TEXT("*"));
	//printf("  %ls   <DIR> num:%d\n", Dirs[0], 0);
	int count_dir = 0;

	while (FindNextFile(hFind, &ffd) != 0)
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			basic_string<TCHAR> fileName = ffd.cFileName;
			if ((fileName == TEXT(".")) || (fileName == TEXT("..")))
			{
				continue;
			}
			// string to a buffer, then append '\*' to the directory name.

			StringCchCopy(Dirs[count_dir++], MAX_PATH, ffd.cFileName);
			//printf("  %ls   <DIR> num:%d\n", Dirs[count_dir - 1], count_dir - 1);
		}
		if (exit_image_processing) return 0;
	}


	for (int i = 0; i < count_dir + 1; i++) {
		StringCchCopy(szDir_In, MAX_PATH, path_in);
		if (count_dir == 0) {
			StringCchCat(szDir_In, MAX_PATH, TEXT("\\*"));
		}
		else {
			StringCchCat(szDir_In, MAX_PATH, TEXT("\\"));
			StringCchCat(szDir_In, MAX_PATH, Dirs[i]);
			StringCchCat(szDir_In, MAX_PATH, TEXT("\\*"));
		}


		hFind = FindFirstFile(szDir_In, &ffd);
		// List all the files in the directory with some info about them.
		do
		{
			if (exit_image_processing) return 0;

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
				if (count_dir == 0) {
					StringCchCat(szDir, MAX_PATH, TEXT("\\"));
				}
				else {
					StringCchCat(szDir, MAX_PATH, TEXT("\\"));
					StringCchCat(szDir, MAX_PATH, Dirs[i]);
					StringCchCat(szDir, MAX_PATH, TEXT("\\"));
				}
				StringCchCat(szDir, MAX_PATH, ffd.cFileName);
				wstring wfname_in(szDir);
				image = cv::imread(cv::samples::findFile(string(wfname_in.begin(), wfname_in.end())), cv::IMREAD_COLOR); // Read the file
				if (image.empty())                      // Check for invalid input
				{
					printf("Error: Could not open or find the image\n");
					continue;
				}

				width = image.cols;
				height = image.rows;

				extern int  Img_Size_Type;
				if ((width == 800) && (height == 800)) {
					//DeleteFile(szDir);
					//continue;
				}
				else if ((width == 800) && (height == 640)) {
					//DeleteFile(szDir);
					//continue;
				}
				else if ((width == 1200) && (height == 960)) {
					//continue;
				}
				else if ((width == 1500) && (height == 1200)) {
					//1500x1200
					//1400x1120
					//continue;
				}
				else if ((width == 1400) && (height == 1120)) {
					//continue;
				}
				else {
					//DeleteFile(szDir);
					continue;
				}

				char imgsize[40];
				sprintf_s(imgsize, "%dx%d", image.cols, image.rows);
				
				if (strcmp(imgsize, old_imgsize) != 0)
				{
					Read_Logo_Text_Array(imgsize);
					Read_Logo_Shadow_Array(imgsize);
				}
				strcpy_s(old_imgsize, 40, imgsize);
				System::String^ imgsize_string = image.cols.ToString() + "x" + image.rows.ToString();
				Image_Processing_New(&image, imgsize_string);


				StringCchCopy(szDir_Out, MAX_PATH, path_out);
				StringCchCat(szDir_Out, MAX_PATH, TEXT("\\"));
				StringCchCat(szDir_Out, MAX_PATH, Dirs[i]);

				CreateDirectory(szDir_Out, NULL);

				StringCchCat(szDir_Out, MAX_PATH, TEXT("\\"));
				StringCchCat(szDir_Out, MAX_PATH, ffd.cFileName);

				vector<int> compression_params;
				compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
				compression_params.push_back(compression);
				string path_write = "";
				//MarshalString(szDir_Out, path_write);

				path_write = std::string(&szDir_Out[0], &szDir_Out[MAX_PATH - 1]);
				cv::putText(image, "TEST PHOTOS", cv::Point(image.rows / 2 - 220, image.cols / 2 - 120), cv::FONT_HERSHEY_TRIPLEX, 2, cv::Scalar(10, 10, 255), 6, CV_AA);
				cv::imwrite(path_write, image, compression_params);
			}
		} while (FindNextFile(hFind, &ffd) != 0);
	}


	FindClose(hFind);
	return 0;
}
