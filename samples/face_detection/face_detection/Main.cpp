#include "FaceData.hpp"
#include "FaceDetectorCpu.hpp"
#include "FaceDetectorCL.hpp"
#include "WorkThreadWin32.hpp"

//#include "..\\..\src\device_ocl.h"
#include <device_ocl.h>

#include <windows.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <process.h>
#include <stdlib.h>

using namespace cv;
using namespace std;


#define THREAD_NUM_CPU 12
#define THREAD_NUM_CL 12

void camera_work(bool isGPU){
	FaceDetectorCpu faceDetector("face_single_cpu");;
	FaceDetectorCL faceDetectorCL("face_single_CL");

	faceDetector.load(EYE_TREE_EYEGLASSES_DATA);
	faceDetectorCL.load(EYE_TREE_EYEGLASSES_DATA);

    int id = -1;
	for(int i=0; i<15; i++){
		VideoCapture cap(i);
		if(cap.isOpened()){
			id = i; break;
		}
	}
	CvCapture* capture = 0;
    Mat frame, frameCopy, image;
	
    capture = cvCaptureFromCAM( id ); //0=default, -1=any camera, 1..99=your camera
    if(!capture) cout << "No camera detected" << endl;
	
    cvNamedWindow( "result", 1 );

	unsigned int count = 0;

    if( capture )
    {
        cout << "In capture ..." << endl;
        for(;;)
        {
			count++;
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
			if(isGPU) {
				faceDetectorCL.setSrcImg(frame, 1);
				faceDetectorCL.doWork();
				cv::imshow("result", faceDetectorCL.resultMat());
			}
			else {
				faceDetector.setSrcImg(frame, 1);
				faceDetector.doWork();
				cv::imshow("result", faceDetector.resultMat());
			}
            if( waitKey( 10 ) >= 0 ){
                cvReleaseCapture( &capture );
				break;
			}
        }
	}
    waitKey(0);

    cvDestroyWindow("result");

    return ;
}


#define FACE_IMG_01 "..\\images\\face01.jpg"
#define FACE_IMG_02 "..\\images\\face02.jpg"
#define FACE_IMG_03 "..\\images\\face03.jpg"
#define FACE_IMG_04 "..\\images\\face04.jpg"
#define FACE_IMG_LENA "..\\images\\lena.jpg"

#define FACE_MY_1 "..\\images\\my1.jpg"

void image_work(){
	
	IplImage *ipl = cvLoadImage(FACE_MY_1);
	cv::Mat img(ipl);
	
	/*
	cv::imshow("", img);
	cv::waitKey(0);
	*/

	cv::Mat matDst;

	FaceDetectorCpu faceDetector("image_CPU");
	faceDetector.load(EYE_TREE_EYEGLASSES_DATA);
	faceDetector.setSrcImg(img, 1);
	faceDetector.doWork();
	cv::imshow("result", faceDetector.resultMat());
	cv::waitKey(0);
}


#define VIDEO_400x240 "..\\images\\400x240.mp4"
#define VIDEO_480x272 "..\\images\\480x272.mp4"
#define VIDEO_VGA "..\\images\\640x480_vga.mp4"
#define VIDEO_720p "..\\images\\720p.mp4"
#define VIDEO_1080p "..\\images\\1080p.mp4"


void video_work_CL(){

	int count = THREAD_NUM_CL;
	std::vector<FaceDetectorCL> faceDetectorCL;

	for(int i=0; i<count; i++){
		std::string str = "face";
		char num[5];
		itoa(i, num, 10);
		str += num;
		FaceDetectorCL *detector;
		detector = new FaceDetectorCL(str.c_str());
		detector->setVideoFile(VIDEO_VGA);
		faceDetectorCL.push_back(*detector);
		_beginthread( video_thread_CL, 0, detector);
	}

	while( 1 ){
		Sleep( 1000 );
		if( waitKey( 10 ) >= 0 ){
			break;
		}
	}

	return;
}

void video_work_Cpu(){
	int count = THREAD_NUM_CPU;
	std::vector<FaceDetectorCpu> faceDetector;
	
	for(int i=0; i<count; i++){
		std::string str = "face";
		char num[5];
		itoa(i, num, 10);
		str += num;
		FaceDetectorCpu *detector;
		detector = new FaceDetectorCpu(str.c_str());
		detector->setVideoFile(VIDEO_VGA);
		faceDetector.push_back(*detector);
		_beginthread( video_thread_CPU, 0, detector);
	}

	while( 1 ){
		Sleep( 1000 );
		if( waitKey( 10 ) >= 0 ){
			break;
		}
	}
	return;
}

int main(){

	//cv::ocl::setDevice function (with cv::ocl::getOpenCLPlatforms and cv::ocl::getOpenCLDevices).
	bool clDeviceFound = false;
	
	std::string platformName = "AMD";
	//std::string platformName = "Intel";
	cv::ocl::DeviceType deviceType = cv::ocl::DeviceType::CVCL_DEVICE_TYPE_GPU;
	
	DeviceOcl devOcl;
	
	if(0){
		clDeviceFound = devOcl.setDevice(platformName.c_str(), deviceType);
	}
	
	if(0){
		clDeviceFound = devOcl.setDeviceFromAnyPlatform(deviceType);
	}
	
	//image_work();
	//camera_work(isGPU);
	//video_work(isGPU);
	if(clDeviceFound){ video_work_CL();	}
	else { video_work_Cpu(); }
    
	return 0;
}
