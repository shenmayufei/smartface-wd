#pragma once

#include "opencv2\core\core.hpp"
#include "Buffer.h"

#include <mutex>
#include <map>

class SharedImageBuffer
{
public:
	SharedImageBuffer();
	~SharedImageBuffer();

	void add(int deviceNumber, Buffer<cv::Mat> * buffer);
	Buffer<cv::Mat> * getByDeviceNumber(int deviceNumber);
	void removeByDeviceNumber(int deviceNumber);

private:
	std::map<int, Buffer<cv::Mat> *> imageBuffered;
	std::mutex mLock;
};

