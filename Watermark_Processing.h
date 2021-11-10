#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <windows.h>
//using namespace cv;
using namespace std;

#define LOGO_HEIGHT 142
#define LOGO_WIDTH 680

void Watermark_Processing(cv::Mat *image, float *contour_back, float *contour_font);
void Watermark_Processing_1200_960(cv::Mat *image, float *contour_back, float *contour_font);
void Watermark_Text_Processing(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name);
void Watermark_Text_Processing_1200_960(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name);
void Watermark_Text_Processing_1500x1200(int row_start, int row_end, int col_start, int col_end, int offset_left, string &name);
void Save_White(char *size);
void Read_White(char *size);
void Save_Shadow(char *size);
void Read_Shadow(char *size);
void Save_Artifact(char *size);
void Read_Artifact(char *size);
void Check_Size(char *size, char *data_red, char *data_green, char *data_blue);
extern float shadow[LOGO_HEIGHT][LOGO_WIDTH][3];
extern float artifact[LOGO_HEIGHT][LOGO_WIDTH][3];
void Read_Settings_Fast(char *str);

extern float red_white[LOGO_HEIGHT][LOGO_WIDTH];
extern float green_white[LOGO_HEIGHT][LOGO_WIDTH];
extern float blue_white[LOGO_HEIGHT][LOGO_WIDTH];

extern float learn_contour_back[4];
extern float learn_contour_front[4];
extern float process_contour_back[4];
extern float process_contour_front[4];

extern float process_white_front[3];
extern float process_white_back[3];
extern float learn_white_front[3];
extern float learn_white_back[3];
extern bool enable_all_button;
extern char *path_in;
extern char *path_out;
extern bool exit_image_processing;
extern bool enable_stop_processing_images;
extern int compression;

extern cv::Mat Image_In;
extern cv::Mat Image_Out;


#define LOGO_ROW_START 315
#define LOGO_WINDOW_HEIGHT 142
#define LOGO_COL_START 60
#define LOGO_WINDOW_WIDTH 680


extern TCHAR*  Open_in;
extern TCHAR*  Open_out;


#define IMG_SIZE_640_800 1
#define IMG_SIZE_800_800 2
#define IMG_SIZE_960_1200 3
#define IMG_SIZE_1500_1200 4

extern int  Img_Size_Type;

extern char data_red_path[100];
extern char data_green_path[100];
extern char data_blue_path[100];


