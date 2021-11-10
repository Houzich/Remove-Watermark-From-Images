#pragma once

//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <string>
//using namespace cv;
//using namespace std;

void Learning_Processing_800x800(float *f_back, float *f_font);
void Learning_Processing_1200x960(float *f_back, float *f_font);
void Learning_Processing(const char *str);
void Erosion(int, void*);
void Dilation(int, void*);
void Learning_Artifact_1200_960(int limit_1, int limit_2, int limit_3, int color_offset);

