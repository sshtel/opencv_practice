#include "FaceData.hpp"
#include "FaceDetector.hpp"
#include "FaceDetectorCL.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;
using namespace std;


void camera_work(){
	
	
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

    if( capture )
    {
        cout << "In capture ..." << endl;
        for(;;)
        {
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
            if( frame.empty() )
                break;
            if( iplImg->origin == IPL_ORIGIN_TL )
				frame.copyTo( frameCopy );
            else
                flip( frame, frameCopy, 0 );

			if(1)
			{
				faceDetector.setSrcImg(frameCopy);
				faceDetector.doWork();
				cv::imshow("result", faceDetector.resultMat());
			}
			if(0){
				faceDetectorCL.setSrcImg(frameCopy, 1);
				faceDetectorCL.doWork();
				cv::imshow("result", faceDetectorCL.resultMat());
			}
			
            if( waitKey( 10 ) >= 0 )
                cvReleaseCapture( &capture );
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

void image_work(){
	
	IplImage *ipl = cvLoadImage(FACE_IMG_LENA);
	cv::Mat img(ipl);
	
	/*
	cv::imshow("", img);
	cv::waitKey(0);
	*/

	cv::Mat matDst;

	FaceDetector faceDetector;
	faceDetector.setSrcImg(img);
	faceDetector.cutEyes();
	faceDetector.showImage(faceDetector.resultMat());

}



int main(){
	
	//image_work();
	camera_work();

	return 0;
}
