#include "FaceDetectorCL.hpp"
#include "FaceData.hpp"

using namespace cv;

FaceDetectorCL::FaceDetectorCL(){
	
}

int FaceDetectorCL::load(std::string path){
	dataPath_ = path;

	
    if( !cascade_.load( path ))
    {
        std::cout << "ERROR: Could not load classifier cascade: " << path << std::endl;
        return -1;
    }

	return 0;
}

void FaceDetectorCL::setSrcImg(cv::Mat &src, double scale){
	this->matSrc_ = src;
	src.copyTo(this->matResult_);
	//if(this->matResult_.empty()) src.copyTo(this->matResult_);
	if(this->omatSrc_.empty()) this->omatSrc_ = cv::ocl::oclMat( src.rows, src.cols, src.type() );
	if(this->omatGray_.empty()) this->omatGray_ = cv::ocl::oclMat( cvRound (src.rows/scale), cvRound(src.cols/scale), CV_8UC1 );
}

int FaceDetectorCL::doWork(){
	if(dataPath_ == FRONT_FACE_DEFAULT_DATA){
		return cutFace();
	}
	else if(dataPath_ == EYE_DATA){
		return cutEyes();
	}
	else if(dataPath_ == EYE_TREE_EYEGLASSES_DATA){
		return cutEyes();
	}

	return -1;
}

int FaceDetectorCL::cutFace(){
	
	omatSrc_.upload(matSrc_);

    cv::ocl::cvtColor( omatSrc_, omatGray_, CV_BGR2GRAY );
    //cv::ocl::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    //cv::ocl::equalizeHist( omatGray_, omatGray_ );
	
	std::vector<cv::Rect> faces;
    cascade_.detectMultiScale( omatGray_, faces, 1.1,
                              3, 0
                              |CV_HAAR_SCALE_IMAGE
                              , Size(150,150), Size(0, 0) );
    
	
	
	for(int i=0; i<faces.size(); i++) {
        cv::Point lb(faces[i].x + faces[i].width,
                        faces[i].y + faces[i].height);
        cv::Point tr(faces[i].x, faces[i].y);
 
		cv::rectangle(this->matResult_, lb, tr, cv::Scalar(0,255,0), 3, 4, 0);
    }
	
	return 0;

}

int FaceDetectorCL::cutEyes(){
	
	omatSrc_.upload(matSrc_);

    cv::ocl::cvtColor( omatSrc_, omatGray_, CV_BGR2GRAY );
    //cv::ocl::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    //cv::ocl::equalizeHist( omatGray_, omatGray_ );
	
	std::vector<cv::Rect> faces;
    cascade_.detectMultiScale( omatGray_, faces, 1.1,
                              3, 0
                              |CV_HAAR_SCALE_IMAGE
                              , Size(30,30), Size(0, 0) );
    
	for(int i=0; i<faces.size(); i++) {
        cv::Point lb(faces[i].x + faces[i].width,
                        faces[i].y + faces[i].height);
        cv::Point tr(faces[i].x, faces[i].y);
 
		cv::rectangle(this->matResult_, lb, tr, cv::Scalar(0,255,0), 3, 4, 0);
    }
	
	return 0;

}
