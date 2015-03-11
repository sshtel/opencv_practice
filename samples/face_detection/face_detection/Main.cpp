#include "FaceData.hpp"
#include "FaceDetector.hpp"
#include "FaceDetectorCL.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace std;

void camera_work(bool isGPU){
	FaceDetector faceDetector;
	FaceDetectorCL faceDetectorCL;

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
				faceDetector.setSrcImg(frame);
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

	FaceDetector faceDetector;
	faceDetector.load(EYE_TREE_EYEGLASSES_DATA);
	faceDetector.setSrcImg(img);
	faceDetector.doWork();
	cv::imshow("result", faceDetector.resultMat());
	cv::waitKey(0);
}


#define VIDEO_400x240 "..\\images\\400x240.mp4"
#define VIDEO_480x272 "..\\images\\480x272.mp4"
#define VIDEO_VGA "..\\images\\640x480_vga.mp4"
#define VIDEO_720p "..\\images\\720p.mp4"
#define VIDEO_1080p "..\\images\\1080p.mp4"
void video_work(bool isGPU){
	
	FaceDetector faceDetector;
	FaceDetectorCL faceDetectorCL;
	FaceDetectorCL faceDetectorCL2;

	faceDetector.load(EYE_DATA);
	faceDetectorCL.load(EYE_DATA);
	faceDetectorCL2.load(EYE_DATA);


    int id = -1;
	for(int i=0; i<15; i++){
		VideoCapture cap(i);
		if(cap.isOpened()){
			id = i; break;
		}
	}
	CvCapture* capture = 0;
    Mat frame, frameCopy, image;
	
	capture = cvCaptureFromFile(VIDEO_VGA);
    if(!capture) cout << "No video detected" << endl;
	

	CvCapture* capture2 = 0;
    Mat frame2, image2;
	
	capture2 = cvCaptureFromFile(VIDEO_VGA);
    if(!capture2) cout << "No video2 detected" << endl;
	
	cvNamedWindow( "result", 1 );
	cvNamedWindow( "result2", 1 );

	unsigned int count = 0;

    if( capture )
    {
        cout << "In capture ..." << endl;
        for(;;)
        {
			count++;
			
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
			
			IplImage* iplImg2 = cvQueryFrame( capture2 );
            frame2 = iplImg2;
			
			if(isGPU) {
				faceDetectorCL.setSrcImg(frame, 1);
				faceDetectorCL.doWork();
				cv::imshow("result", faceDetectorCL.resultMat());

				faceDetectorCL2.setSrcImg(frame2, 1);
				faceDetectorCL2.doWork();
				cv::imshow("result2", faceDetectorCL2.resultMat());
			}
			else{
				faceDetector.setSrcImg(frame);
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


int main(){
	bool isGPU = true;
	//image_work();
	//camera_work(isGPU);
	video_work(isGPU);

	return 0;
}
