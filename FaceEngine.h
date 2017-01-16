#pragma once
#include "opencv2\core\core.hpp"
#include "Utils.h"
#include <Windows.h>


#define USER_DATA L"./userdata/"
#define USER_IMAGE L"./userimage/"
#define USER_HISTORY L"./userhist/"

#define USER_DATA_STR "./userdata/"
#define USER_IMAGE_STR "./userimage/"
#define USER_HISTORY_STR "./userhist/"

#define MATCHING_THRESHOLD 70
class FaceEngine
{
public:
	FaceEngine();
	~FaceEngine();

	virtual bool onInit() = 0;
	virtual bool onExit() = 0;
	virtual bool onEnroll(cv::Mat& frame, std::string file) = 0;
	virtual int onMatching(cv::Mat& frame, std::string file) = 0;

	virtual bool isFace(cv::Mat& frame) = 0;

	
};

