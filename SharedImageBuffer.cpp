#include "stdafx.h"
#include "SharedImageBuffer.h"


SharedImageBuffer::SharedImageBuffer()
{
}


SharedImageBuffer::~SharedImageBuffer()
{
}

void SharedImageBuffer::add(int deviceNumber, Buffer<cv::Mat> * buffer)
{
	imageBuffered[deviceNumber] = buffer;
}
Buffer<cv::Mat> * SharedImageBuffer::getByDeviceNumber(int deviceNumber)
{
	return imageBuffered[deviceNumber];
}
void SharedImageBuffer::removeByDeviceNumber(int deviceNumber)
{
	delete imageBuffered[deviceNumber];
	imageBuffered.erase(deviceNumber);
}