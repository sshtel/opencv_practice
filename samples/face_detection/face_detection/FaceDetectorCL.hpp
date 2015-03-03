#ifndef __FACE_DETECTOR_CL_H
#define __FACE_DETECTOR_CL_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/ocl/ocl.hpp>


class FaceDetectorCL{

private:
	cv::Mat matSrc_;
	cv::Mat matResult_;

	cv::ocl::oclMat omatSrc_;
	cv::ocl::oclMat omatDst_;
	cv::ocl::oclMat omatGray_;
	
	std::string dataPath_;
	
	bool isGray(cv::Mat &src);

	cv::ocl::OclCascadeClassifier cascade_;

public:
	FaceDetectorCL();

	
	int load(std::string path);
	void setSrcImg(cv::Mat &src, double scale);
	int doWork();
	int cutFace();
	int cutEyes();
	
	cv::Mat& resultMat() { return this->matResult_; }
	
	void showImage(cv::Mat &mat)
	{
		cv::Mat img(mat);
		cv::imshow("show", img);
		cv::waitKey(0);
	}


};


#endif