#ifndef __DEVICE_OCL_H
#define __DEVICE_OCL_H

using namespace cv::ocl;

class DeviceOcl {
public:
	bool setDevice(const char* platformName, cv::ocl::DeviceType deviceType);
	
	bool setDeviceFromAnyPlatform(cv::ocl::DeviceType deviceType);

};



#endif