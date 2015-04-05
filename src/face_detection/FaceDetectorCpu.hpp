#ifndef __FACE_DETECTOR_CPU_H
#define __FACE_DETECTOR_CPU_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "FaceDetector.hpp"

class FaceDetectorCpu : public FaceDetector{

private:
	std::string name_;
	std::string videoFile_;

	cv::Mat matSrc_;
	cv::Mat matGray_;

	std::string dataPath_;

	bool isGray(cv::Mat &src);
	cv::CascadeClassifier face_classifier_;
public:
	explicit FaceDetectorCpu(std::string name);
	std::string name() { return name_; }
	void setVideoFile(std::string file) { videoFile_ = file;}
	std::string videoFile() { return videoFile_; }


	int load(std::string path);
	void setSrcImg(cv::Mat &src, double scale);
	int doWork();
	int cutFace();
	int cutEyes();

	cv::Mat& resultMat() { return this->matSrc_; }
	
	void showImage(cv::Mat &mat)
	{
		cv::Mat img(mat);
		cv::imshow("show", img);
		cv::waitKey(0);
	}


};


#endif