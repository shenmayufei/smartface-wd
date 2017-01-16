#pragma once
#include "opencv2\core\core.hpp"
#include "Viewer.h"
class VerifyViewer: public Viewer
{
public:
	virtual void showText(LPCTSTR text) = 0;
	virtual void showTime(std::string time) = 0;
	//virtual void showFrame(cv::Mat& frame) = 0;
};