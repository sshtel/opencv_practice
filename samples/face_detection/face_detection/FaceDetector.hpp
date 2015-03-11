#ifndef __CASCADE_CLASSIFIER_H
#define __CASCADE_CLASSIFIER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

class FaceDetector{

private:
	cv::Mat matSrc_;
	cv::Mat matGray_;

	std::string dataPath_;
	
	bool isGray(cv::Mat &src);
	cv::CascadeClassifier face_classifier_;
public:
	FaceDetector();

	int load(std::string path);
	void setSrcImg(cv::Mat &src);
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