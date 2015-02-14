#ifndef __CASCADE_CLASSIFIER_H
#define __CASCADE_CLASSIFIER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

class FaceDetector{

private:
	cv::Mat matSrc_;
	cv::Mat matDst_;

	cv::Mat matGray_;

	std::string dataPath_;
	
	bool isGray(cv::Mat &src);

public:
	FaceDetector();

	void setDataPath(std::string path);
	void setSrcImg(cv::Mat &src);
	int cutFace(cv::Mat &dst);
	int cutEyes(cv::Mat &dst);

	
	void showImage(cv::Mat &mat)
	{
		cv::Mat img(mat);
		cv::imshow("show", img);
		cv::waitKey(0);
	}


};



#endif