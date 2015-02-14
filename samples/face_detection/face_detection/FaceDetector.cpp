#include "FaceDetector.h"

FaceDetector::FaceDetector(){
	
}

void FaceDetector::setDataPath(std::string path){
	dataPath_ = path;
	//dataPath_ = "haarcascade_frontalface_default.xml";
}

void FaceDetector::setSrcImg(cv::Mat &src){
	this->matSrc_ = src;
}


#define FRONT_FACE_DEFAULT_DATA "..\\..\\..\\opencv\\data\\haarcascades\\haarcascade_frontalface_default.xml"
//#define FRONT_FACE_DEFAULT_DATA "D:/workspace/opencv_practice/opencv_practice/samples/face_detection/images/haarcascade_frontalface_default.xml"


int FaceDetector::cutFace(cv::Mat &dst){
	setDataPath(FRONT_FACE_DEFAULT_DATA);
	
	cv::CascadeClassifier face_classifier;
	if(	!face_classifier.load(this->dataPath_)  ){
		return -1;
	}
	
	cv::cvtColor(matSrc_, matGray_, CV_BGR2GRAY);		

	//cv::equalizeHist(matGray_, matGray_);
	//cv::GaussianBlur(matGray_, matGray_, cv::Size(3, 3), 1, 1);
	//this->showImage(matGray_);
	std::vector<cv::Rect> faces;
	
	face_classifier.detectMultiScale(matGray_, faces, 
		1.1, 
		3,
		CV_HAAR_SCALE_IMAGE,
		cv::Size(150, 150));

	for(int i=0; i<faces.size(); i++) {
        cv::Point lb(faces[i].x + faces[i].width,
                        faces[i].y + faces[i].height);
        cv::Point tr(faces[i].x, faces[i].y);
 
		cv::rectangle(this->matSrc_, lb, tr, cv::Scalar(0,255,0), 3, 4, 0);
    }
	
	this->showImage(this->matSrc_);
	
	return 0;
}

#define EYE_DATA "..\\..\\..\\opencv\\data\\haarcascades\\haarcascade_eye.xml"
#define EYE_TREE_EYEGLASSES_DATA "..\\..\\..\\opencv\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml"

int FaceDetector::cutEyes(cv::Mat &dst){
	//setDataPath(EYE_DATA);
	setDataPath(EYE_TREE_EYEGLASSES_DATA);
	
	cv::CascadeClassifier face_classifier;
	if(	!face_classifier.load(this->dataPath_)  ){
		return -1;
	}
	
	
	cv::cvtColor(matSrc_, matGray_, CV_BGR2GRAY);		
	
	//cv::equalizeHist(matGray_, matGray_);
	//cv::GaussianBlur(matGray_, matGray_, cv::Size(3, 3), 1, 1);
	//this->showImage(matGray_);
	std::vector<cv::Rect> faces;
	
	face_classifier.detectMultiScale(matGray_, faces, 
		1.1, // must be bigger than 1.0
		3,
		CV_HAAR_SCALE_IMAGE,
		cv::Size(30, 30));

	for(int i=0; i<faces.size(); i++) {
        cv::Point lb(faces[i].x + faces[i].width,
                        faces[i].y + faces[i].height);
        cv::Point tr(faces[i].x, faces[i].y);
 
		cv::rectangle(this->matSrc_, lb, tr, cv::Scalar(0,255,0), 3, 4, 0);
    }
	
	this->showImage(this->matSrc_);
	
}

bool FaceDetector::isGray(cv::Mat &src){
	if(src.channels() == 1) return true;
	return false;
}
