#include <iostream>
#include <windows.h>
#include <process.h>
#include <opencv2\opencv.hpp>
#include "WorkThreadWin32.hpp"

#define THREAD_NUM_CPU 3
#define THREAD_NUM_CL 3



void work_CL(){
	
	for(int i=0; i<THREAD_NUM_CL; i++){
		_beginthread( display_thread, 0, 0);
	}

	while( 1 ){
		Sleep( 1000 );
		if( cv::waitKey( 10 ) >= 0 ){
			break;
		}
	}


}



int main(){
	return 0;
}