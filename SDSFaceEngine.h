#pragma once
#include "FaceEngine.h"
#include "SDSFace310W.h"

class SDSFaceEngine :
	public FaceEngine
{
public:
	SDSFaceEngine();
	~SDSFaceEngine();

	virtual bool onInit();
	virtual bool onExit();
	virtual bool onEnroll(cv::Mat& frame, std::string file);
	virtual int onMatching(cv::Mat& frame, std::string file);
	virtual bool isFace(cv::Mat& frame);
private:

};

