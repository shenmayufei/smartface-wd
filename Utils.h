#pragma once
#include "opencv2\core\core.hpp"
#include <mmsystem.h>
#include "SDSFace310W.h"
#include <fstream>
#include <time.h>
#include <algorithm>
class Utils
{
public:
	Utils();
	~Utils();

	static int Mat2CImage(cv::Mat& mat, CImage& cImage);
	static std::string CString2String(const CString cstr);
	static CString String2CString(const std::string str);
	static bool playSound(LPCWSTR file);
	static bool serilizeFeature(DETECTRESULT * feature, std::string file);
	static DETECTRESULT loadFeature(std::string file);
	
	static std::string getCurrentDatetime();
	static std::string getDate(std::string dateTime);
	static std::string getTime(std::string dateTime);
	static std::string formatDateTime(std::string dateTime);
};

