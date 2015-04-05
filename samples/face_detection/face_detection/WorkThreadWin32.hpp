#ifndef __WORK_THREAD_WIN32_H
#define __WORK_THREAD_WIN32_H
#include <opencv/cv.h>
#include <opencv/highgui.h>

void display_thread(void* params);
void video_thread_CL(void* pParams);
void video_thread_CPU(void* pParams);


#endif