#pragma once
#include "opencv2\core\core.hpp"
class Viewer
{
public:
	virtual void showFrame(cv::Mat& frame) = 0;
};