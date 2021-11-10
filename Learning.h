#pragma once
#include <string>

#define LOGO_HEIGHT 142
#define LOGO_WIDTH 680

typedef float LogoArr[LOGO_HEIGHT][LOGO_WIDTH][3];


class LogoLearning {

	public:
		std::string imageName;
		float color_back[3] = { 0.0,0.0,0.0 };
		float color_front[3] = { 0.0,0.0,0.0 };
		int img_row_start;
		int img_col_start;
		int window_row_start = 0;
		int window_col_start = 0;
		int window_height;
		int window_width;
		float(*arr)[LOGO_HEIGHT][LOGO_WIDTH][3];
};

void Shadow_Learning(LogoLearning* dt, int step);

