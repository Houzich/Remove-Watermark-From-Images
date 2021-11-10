
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#include "Copy_Image.h"

using namespace std;
//using namespace System;
//using namespace System::Windows::Forms;


int Copy_Image(TCHAR* path_in, TCHAR* path_out)
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


	StringCchCopy(Dirs[0], MAX_PATH, TEXT("*"));
	//printf("  %ls   <DIR> num:%d\n", Dirs[0], 0);
	int count_dir = 1;

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
	}


	for(int i = 0; i < count_dir; i++){
		StringCchCopy(szDir_In, MAX_PATH, path_in);
		StringCchCat(szDir_In, MAX_PATH, TEXT("\\"));
		StringCchCat(szDir_In, MAX_PATH, Dirs[i]);
		StringCchCat(szDir_In, MAX_PATH, TEXT("\\*"));

		hFind = FindFirstFile(szDir_In, &ffd);
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
			StringCchCat(szDir, MAX_PATH, Dirs[i]);
			StringCchCat(szDir, MAX_PATH, TEXT("\\"));
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
				continue;
			}
			else if ((width == 1200) && (height == 960)) {
				DeleteFile(szDir);
				continue;
			}
			else if ((width == 1500) && (height == 1200)) {
				//DeleteFile(szDir);
				//1500x1200
				//1400x1120
				continue;
			}
			else if ((width == 1400) && (height == 1120)) {
				DeleteFile(szDir);
				continue;
			}
			else {
				DeleteFile(szDir);
				continue;
			}

			StringCchCopy(szDir_Out, MAX_PATH, path_out);
			StringCchCat(szDir_Out, MAX_PATH, TEXT("\\"));
			StringCchCat(szDir_Out, MAX_PATH, ffd.cFileName);
			if (CopyFile(szDir, szDir_Out, FALSE))
			{
				DeleteFile(szDir);
			}
			else
			{
				printf("Could not copy file.\n");
				//return (-1);
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);
	}


	FindClose(hFind);
	return 0;
}


