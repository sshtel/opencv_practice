#include "WorkThreadWin32.hpp"
#include "FaceData.hpp"
#include "FaceDetectorCpu.hpp"
#include "FaceDetectorCL.hpp"

#include <opencv/cv.h>
#include <opencv/highgui.h>


#include <windows.h>
#include <process.h>

using namespace std;
using namespace cv;


#ifdef WIN32
void video_thread_CL(void* pParams)
{
	FaceDetectorCL *p_faceDetector = (FaceDetectorCL*)pParams;
	FaceDetectorCL &faceDetector = * p_faceDetector;
	std::string name = faceDetector.name();
	
	//EYE_TREE_EYEGLASSES_DATA
	//EYE_DATA
	//FRONT_FACE_DEFAULT_DATA
	faceDetector.load(FRONT_FACE_DEFAULT_DATA);

	CvCapture* capture = 0;
    Mat frame, frameCopy, image;
	
	capture = cvCaptureFromFile(faceDetector.videoFile().c_str());
    if(!capture) cout << "No video detected" << endl;
	
	cvNamedWindow( name.c_str(), 1 );
	
	unsigned int count = 0;
	
    if( capture )
    {
        cout << "In capture ..." << name.c_str() << endl;
        for(;;)
        {
			count++;
			
            IplImage* iplImg = cvQueryFrame( capture );
			if(!iplImg) break;
            frame = iplImg;
			
			faceDetector.setSrcImg(frame, 1);
			faceDetector.doWork();
			cv::imshow(name.c_str(), faceDetector.resultMat());
			
			
            if( waitKey( 10 ) >= 0 ){
                cvReleaseCapture( &capture );
				break;
			}
			
			
			Sleep(1);
        }
	}
    waitKey(0);

    cvDestroyWindow(name.c_str());
	_endthread();
    return ;

}


void video_thread_CPU(void* pParams){
	
	FaceDetectorCpu *p = (FaceDetectorCpu*)pParams;
	FaceDetectorCpu &faceDetector = *p;
	std::string name = faceDetector.name();
	
	//EYE_TREE_EYEGLASSES_DATA
	//EYE_DATA
	//FRONT_FACE_DEFAULT_DATA
	faceDetector.load(FRONT_FACE_DEFAULT_DATA);

	CvCapture* capture = 0;
    Mat frame, frameCopy, image;
	
	capture = cvCaptureFromFile(faceDetector.videoFile().c_str());
    if(!capture) cout << "No video detected" << endl;
	
	cvNamedWindow(name.c_str(), 1 );
	
	unsigned int count = 0;

    if( capture )
    {
        cout << "In capture ..." << name.c_str() << endl;
        for(;;)
        {
			count++;
			
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
			
			faceDetector.setSrcImg(frame, 1);
			faceDetector.doWork();
			cv::imshow(name.c_str(), faceDetector.resultMat());
			
            if( waitKey( 10 ) >= 0 ){
                cvReleaseCapture( &capture );
				break;
			}
        }
	}
    waitKey(0);

    cvDestroyWindow(name.c_str());
	_endthread();
    return ;


}



#endif
