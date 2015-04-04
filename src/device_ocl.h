#ifndef __DEVICE_OCL_H
#define __DEVICE_OCL_H

#include <opencv2/ocl/ocl.hpp>

using namespace cv::ocl;

class DeviceOcl {
public:
	static bool setDevice(const char* platformName, cv::ocl::DeviceType deviceType){
		bool clDeviceFound = false;
		cv::ocl::PlatformsInfo platformsInfo;
		cv::ocl::getOpenCLPlatforms(platformsInfo);
		//find platform and device using PlatformInfo::platformVersion
		
		int size = platformsInfo.size();
		for(int i=0; i<size; i++){
			const cv::ocl::PlatformInfo *pInfo = platformsInfo.at(i);
			int pos = pInfo->platformName.find(platformName);  //WARNING!  this is not common way to find device. you better choose platform using getOpenCLDevices
			if(pos >= 0){
				//platform found!
				
				for(int dev_cnt = 0; dev_cnt < pInfo->devices.size(); dev_cnt++){
					const cv::ocl::DeviceInfo *dev = pInfo->devices[dev_cnt];
					if(dev->deviceType == deviceType){
						cv::ocl::setDevice(dev);
						return true;
					}
				}
			}
		}

		return false;
	}
	
	static bool setDeviceFromAnyPlatform(cv::ocl::DeviceType deviceType){
		cv::ocl::PlatformsInfo platformsInfo;
		cv::ocl::getOpenCLPlatforms(platformsInfo);
		//find device using getOpenCLDevices
		int size = platformsInfo.size();
		for(int i=0; i<size; i++){
			const cv::ocl::PlatformInfo *pInfo = platformsInfo.at(i);
			cv::ocl::DevicesInfo devicesInfo;
			int ret = cv::ocl::getOpenCLDevices(devicesInfo, deviceType, pInfo); //get ANY device of that type.
			if(ret) { 
				cv::ocl::setDevice(devicesInfo.at(0));
				return true;
			}
		}
		return false;
	}


};



#endif