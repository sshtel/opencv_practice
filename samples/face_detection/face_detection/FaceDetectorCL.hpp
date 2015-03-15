#ifndef __FACE_DETECTOR_CL_H
#define __FACE_DETECTOR_CL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ocl/ocl.hpp>
#include "WorkThreadWin32.hpp"
#include "FaceDetector.hpp"

class FaceDetectorCL : public FaceDetector{

private:
	std::string name_;
	std::string videoFile_;

	cv::Mat matSrc_;
	
	cv::ocl::oclMat omatSrc_;
	cv::ocl::oclMat omatGray_;
	
	std::string dataPath_;
	
	bool isGray(cv::Mat &src);

	cv::ocl::OclCascadeClassifier cascade_;
	

public:
	explicit FaceDetectorCL(std::string name);
	std::string name() { return name_; }
	void setVideoFile(std::string file) { videoFile_ = file;}
	std::string videoFile() { return videoFile_; }

	int load(std::string path);
	void setSrcImg(cv::Mat &src, double scale);
	int doWork();
	int cutFace();
	int cutEyes();
	
	virtual cv::Mat& resultMat() { return this->matSrc_; }

	void showImage(cv::Mat &mat)
	{
		cv::Mat img(mat);
		cv::imshow("show", img);
		cv::waitKey(0);
	}

};


#endif