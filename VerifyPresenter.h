#pragma once
#include "VerifyViewer.h"
#include "CameraVerifyThread.h"
#include "Presenter.h"
#include "CameraThread.h"
#include "CameraDisplayThread.h"
#include "DisplayViewer.h"
#include "opencv2\imgproc\imgproc.hpp"
#include <mutex>
#include "VerifyDialog.h"
#include "TimeThread.h"

//class VerifyDialog;
//class CameraVerifyThread;
class TimeThread;

class CameraVerifyThread;
class VerifyPresenter :
	public Presenter
{
public:
	VerifyPresenter(VerifyViewer *viewer);
	~VerifyPresenter();
	virtual bool onInit();
	virtual void onRun();
	virtual void onPause();
	virtual void onResume();
	virtual bool onExit();
	//virtual void onProcessFrame();
	
	virtual void onVerifyFrame();
	//virtual void playSound(LPCWSTR file);
	virtual void onStartVerify(int num, std::string number);
	virtual void showTime(std::string time);
private:
	CameraDisplayThread *mDisplay;
	CameraThread * mCam;
	CameraVerifyThread * mVerifyThread;
	TimeThread * tThread;
	std::vector<User> mUsers;

	//VerifyViewer * mViewer;

	int mNum;
	//std::mutex lock;
};

