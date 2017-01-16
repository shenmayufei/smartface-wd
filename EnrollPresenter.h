#pragma once
#include "DisplayViewer.h"
#include "EnrollDialog.h"
#include "CameraThread.h"
#include "CameraDisplayThread.h"
#include "Presenter.h"
#include "opencv2\imgproc\imgproc.hpp"
#include <sstream>

class DisplayViewer;

class EnrollPresenter :
	public Presenter
{
public:
	EnrollPresenter(DisplayViewer *viewer);
	~EnrollPresenter();

	virtual bool onInit();
	virtual void onRun();
	virtual void onPause();
	virtual void onResume();
	virtual bool onExit();
	//virtual void onProcessFrame();


	virtual void onEnroll(std::string name, std::string number);
	virtual void onCapture(int cam);
private:
	int mCaptured;
	CameraDisplayThread *mDisplay;
	CameraThread * mCam;
	//DisplayViewer * mViewer;
};

