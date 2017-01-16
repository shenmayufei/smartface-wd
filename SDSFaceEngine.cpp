#include "stdafx.h"
#include "SDSFaceEngine.h"

SDSFaceEngine::SDSFaceEngine()
{

}


SDSFaceEngine::~SDSFaceEngine()
{
}
bool SDSFaceEngine::onInit()
{
	// create folder

	CreateDirectory(USER_DATA, NULL);
	CreateDirectory(USER_IMAGE, NULL);
	CreateDirectory(USER_HISTORY, NULL);
	int iRet = initializeFR();
	if (iRet = 10003)
	{
		return true;
	}


	
	return false;
}
bool SDSFaceEngine::onExit()
{
	int iRet = terminateFR();
	if (iRet == 10021)
	{
		return true;
	}
	return false;
}
bool SDSFaceEngine::onEnroll(cv::Mat& frame, std::string file)
{
	int faceCount = 0;
	DETECTRESULT * enroll = faceDetectionByBin(frame.data, frame.cols, frame.rows, faceCount);
	if (faceCount > 0 && Utils::serilizeFeature(enroll, file))
	{
		return true;
	}
	return false;
}
int SDSFaceEngine::onMatching(cv::Mat& frame, std::string file)
{
	int faceCount = 0;
	DETECTRESULT * enroll = faceDetectionByBin(frame.data, frame.cols, frame.rows, faceCount);
	if (faceCount > 0)
	{
		DETECTRESULT fet = Utils::loadFeature(file);
		return faceSimilarityByFeature(enroll->feature, fet.feature);
	}
	return -1;
}
bool SDSFaceEngine::isFace(cv::Mat& frame)
{
	int faceCount = 0;
	DETECTRESULT * enroll = faceDetectionByBin(frame.data, frame.cols, frame.rows, faceCount);
	if (faceCount > 0)
	{
		return true;
	}
	return false;
}