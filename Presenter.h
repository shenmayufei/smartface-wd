#pragma once
//#include "Viewer.h"
#include "DatabaseManager.h"
#include "SharedImageBuffer.h"
#include "FaceEngineBuilder.h"
#include "User.h"
#include "Viewer.h"
#include "opencv2\imgproc\imgproc.hpp"
class Viewer;

class Presenter
{
public:
	Presenter(Viewer *mViewer);
	~Presenter();
	virtual bool onInit() = 0;
	virtual void onRun() = 0;
	virtual void onPause() = 0;
	virtual void onResume() = 0;
	virtual bool onExit() = 0;
	virtual void onProcessFrame();

protected:
	Viewer *mViewer;
	DatabaseManager mDBManager;
	SharedImageBuffer * mBuffer;
};

