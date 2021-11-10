#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Threads.h"
#include "Copy_Image.h"
#include "Watermark.h"
#include "Processing.h"
#include <opencv2/imgproc.hpp>


#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;


DWORD WINAPI WatermarkProcessingThreadFunction(LPVOID lpParam);
DWORD WINAPI ImageProcessingThreadFunction(LPVOID lpParam);
DWORD WINAPI CopyImageThreadFunction(LPVOID lpParam);

HANDLE  Array_Of_Thread_Handles[MAX_THAEDS];
HANDLE  hThread_Watermark_Processing;
HANDLE  hThread_Image_Processing;
HANDLE  hThread_CopyImage;

HANDLE  Array_Of_Event_Handles[MAX_THAEDS];
HANDLE  hEvent_Watermark_Processing;
HANDLE  hEvent_Image_Processing;
HANDLE  hEvent_CopyImage;

extern LogoArr	shadow_arr;
extern LogoArr	text_arr;
extern void Image_Processing_New(cv::Mat* image, String^ size);

void Watermark_Close_Threads()
{

	for (int i = 0; i < MAX_THAEDS; i++) {
		// Signal the thread to exit
		::SetEvent(Array_Of_Event_Handles[i]);

		// thread may be suspended, so resume before shutting down
		::ResumeThread(Array_Of_Thread_Handles[i]);
		//// Wait for the thread to exit. If it doesn't shut down
		// on its own, force it closed with Terminate thread
		if (WAIT_TIMEOUT == WaitForSingleObject(Array_Of_Thread_Handles[i], 1000))
		{
			::TerminateThread(Array_Of_Thread_Handles[i], -1000);
		}


		// Close the handle and NULL it out
		// Close all thread handles and free memory allocations.
		::CloseHandle(Array_Of_Thread_Handles[i]);
		Array_Of_Thread_Handles[i] = NULL;

		// Reset the shutdown event
		::ResetEvent(Array_Of_Event_Handles[i]);

	}

}


int Watermark_Threads()
{
	//PMYDATA pDataArray[MAX_THREADS];

	hEvent_Watermark_Processing = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent_Image_Processing = CreateEvent(NULL, FALSE, FALSE, NULL);


	// Create the thread to begin execution on its own.
	hThread_Watermark_Processing = CreateThread(NULL, 0, WatermarkProcessingThreadFunction, 0, 0, NULL);					// returns the thread identifier 
	hThread_Image_Processing = CreateThread(NULL, 0, ImageProcessingThreadFunction, 0, 0, NULL);					// returns the thread identifier 

	// Check the return value for success.
	// If CreateThread fails, terminate execution. 
	// This will automatically clean up threads and memory. 
	if ((hEvent_Watermark_Processing == NULL) || (hEvent_Image_Processing == NULL))
	{
		ErrorHandler(TEXT("CreateEvent"));
		ExitProcess(3);
	}

	if ((hThread_Watermark_Processing != NULL) || (hThread_Image_Processing != NULL))
	{
		ErrorHandler(TEXT("Create Thread"));
		ExitProcess(3);
	}

	// Wait until all threads have terminated.
	// Store Thread handles in Array of Thread
	// Handles as per the requirement
	Array_Of_Event_Handles[0] = hEvent_Watermark_Processing;
	Array_Of_Event_Handles[1] = hEvent_Image_Processing;

	// of WaitForMultipleObjects() 
	Array_Of_Thread_Handles[0] = hThread_Watermark_Processing;
	Array_Of_Thread_Handles[1] = hThread_Image_Processing;

	//WaitForMultipleObjects(1, Array_Of_Thread_Handles, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.
	//CloseHandle(hThread_Display);
	return 0;
}

DWORD WINAPI WatermarkProcessingThreadFunction(LPVOID lpParam)
{
	//using namespace Watermark;
	//string imageLogoTextName = "D:\\ABITANT\\img_in\\1.jpg";
	//string imageLogoTextName = "D:\\ABITANT\\test\\1200x960_4.jpg";
	string imageLogoTextName = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Learn\\" + Image_Size_std + "\\test.jpg";
	cv::Mat image = cv::imread(cv::samples::findFile(imageLogoTextName, cv::IMREAD_COLOR)); // Read the file
		char imgsize[40];
		sprintf_s(imgsize,"%dx%d", image.cols, image.rows);
		Read_Logo_Text_Array(imgsize);
		Read_Logo_Shadow_Array(imgsize);
		Image_Processing_New(&image, Watermark::Watermark::Image_Size);
		//return 1;

	//cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); // Create a window for display.
	//cv::imshow("Display window", image);                // Show our image inside it.
	//CloseHandle(hEvent_Set_Settings);
	//while(1){
	//	Sleep(100);
	//}

	vector<int> compression_params;
	compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
	compression_params.push_back(compression);
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test.jpg", image, compression_params);
	
	imageLogoTextName = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Learn\\" + Image_Size_std + "\\test_1.jpg";
	image = cv::imread(cv::samples::findFile(imageLogoTextName, cv::IMREAD_COLOR)); // Read the file
	Image_Processing_New(&image, Watermark::Watermark::Image_Size);
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test_1.jpg", image, compression_params);

	imageLogoTextName = "D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Learn\\" + Image_Size_std + "\\test_2.jpg";
	image = cv::imread(cv::samples::findFile(imageLogoTextName, cv::IMREAD_COLOR)); // Read the file
	Image_Processing_New(&image, Watermark::Watermark::Image_Size);
	cv::imwrite("D:\\ABITANT\\Soft\\Watermark\\Watermark\\Image_Out\\test_2.jpg", image, compression_params);

	enable_all_button = true;
	return 0;
}

extern int Processing_Folder(TCHAR* path_in, TCHAR* path_out);
DWORD WINAPI ImageProcessingThreadFunction(LPVOID lpParam)
{
	size_t convertedChars = 0;
	size_t newsize = strlen(path_in) + 1;
	wchar_t * wcstring_in = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring_in, newsize, path_in, _TRUNCATE);
	newsize = strlen(path_out) + 1;
	wchar_t * wcstring_out = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring_out, newsize, path_out, _TRUNCATE);

	Processing_Folder(wcstring_in, wcstring_out);
	enable_all_button = true;
	enable_stop_processing_images = false;
	////CloseHandle(hEvent_Set_Settings);
	return 1;
}

DWORD WINAPI CopyImageThreadFunction(LPVOID lpParam)
{
	size_t convertedChars = 0;
	size_t newsize = strlen(path_in) + 1;
	wchar_t* wcstring_in = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring_in, newsize, path_in, _TRUNCATE);
	newsize = strlen(path_out) + 1;
	wchar_t* wcstring_out = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, wcstring_out, newsize, path_out, _TRUNCATE);

	Copy_Image(wcstring_in, wcstring_out);
	return 1;
}



void ErrorHandler(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code.

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

	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	// Free error-handling buffer allocations.

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}