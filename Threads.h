#pragma once
  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TERMINAL_THREADS_H
#define __TERMINAL_THREADS_H
#include <windows.h>




#define MAX_THAEDS 2
extern HANDLE  Array_Of_Thread_Handles[MAX_THAEDS];
extern HANDLE  hThread_Watermark_Processing;
extern HANDLE  hThread_Image_Processing;
extern HANDLE  hThread_CopyImage;

extern HANDLE  Array_Of_Event_Handles[MAX_THAEDS];
extern HANDLE  hEvent_Watermark_Processing;
extern HANDLE  hEvent_Image_Processing;
extern HANDLE  hEvent_CopyImage;

DWORD WINAPI WatermarkProcessingThreadFunction(LPVOID lpParam);
DWORD WINAPI ImageProcessingThreadFunction(LPVOID lpParam);
DWORD WINAPI CopyImageThreadFunction(LPVOID lpParam);

extern char* path_in;
extern char* path_out;
extern bool exit_image_processing;
extern bool enable_stop_processing_images;
extern int compression;
extern bool enable_all_button;
extern TCHAR* Open_in;
extern TCHAR* Open_out;


void ErrorHandler(LPTSTR lpszFunction);
#endif /*__TERMINAL_THREADS_H*/