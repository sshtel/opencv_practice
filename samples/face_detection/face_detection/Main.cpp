#include "FaceDetector.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define FACE_IMG_01 "..\\images\\face01.jpg"
#define FACE_IMG_02 "..\\images\\face02.jpg"
#define FACE_IMG_03 "..\\images\\face03.jpg"
#define FACE_IMG_04 "..\\images\\face04.jpg"


#define FACE_IMG_LENA "..\\images\\lena.jpg"

int main(){
	
	IplImage *ipl = cvLoadImage(FACE_IMG_04);
	cv::Mat img(ipl);
	
	/*
	cv::imshow("", img);
	cv::waitKey(0);
	*/

	cv::Mat matDst;

	FaceDetector faceDetector;
	faceDetector.setSrcImg(img);
	//faceDetector.cutFace(matDst);
	faceDetector.cutEyes(matDst);

	

	return 0;
}
