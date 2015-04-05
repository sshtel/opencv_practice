#ifndef __CASCADE_CLASSIFIER_H
#define __CASCADE_CLASSIFIER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

class FaceDetector{

protected:
	//std::string dataPath_;

public:
	virtual int load(std::string path) = 0;
	virtual void setSrcImg(cv::Mat &src, double scale) = 0;
	virtual int doWork() = 0;
	virtual int cutFace() = 0;
	virtual int cutEyes() = 0;

	virtual cv::Mat& resultMat() = 0;
	
};

#endif