#pragma once
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "Buffer.h"
#include "SharedImageBuffer.h"


#include <mutex>

class CameraThread: public CWinThread
{
public:
	CameraThread(SharedImageBuffer * buffer);
	~CameraThread();

	virtual BOOL InitInstance();
	virtual int Run();
	virtual void Close();
	virtual void onPause();
	virtual void onResume();

private:
	cv::VideoCapture mCap;
	bool isRunning;
	bool isPause;
	std::mutex mLock;
	
	SharedImageBuffer * mImageBuffer;
};

