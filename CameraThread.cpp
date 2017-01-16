#include "stdafx.h"
#include "CameraThread.h"


CameraThread::CameraThread(SharedImageBuffer * buffer) : mImageBuffer(buffer)
{
}


CameraThread::~CameraThread()
{
}

BOOL CameraThread::InitInstance()
{
	if (!mCap.open(0))
	{
		isRunning = false;
		return FALSE;
	}
	
	isRunning = true;
	isPause = false;
	return TRUE;
}
int CameraThread::Run()
{
	
	cv::Mat frame;
	while (isRunning)
	{
		mLock.lock();
		if (!isRunning)
		{
			mImageBuffer->removeByDeviceNumber(0);
			mLock.unlock();
			break;
		}
		mLock.unlock();

		//TRACE("CAMERA THREAD RUNNING\n");
		mLock.lock();
		if (isPause)
		{
			mLock.unlock();
			continue;
		}
		mLock.unlock();
		if (mCap.read(frame))
		{
			mImageBuffer->getByDeviceNumber(0)->add(frame, false);

		}

	}
	return 0;
}
void CameraThread::onPause()
{
	mLock.lock();
	isPause = true;
	mLock.unlock();
}
void CameraThread::onResume()
{
	mLock.lock();
	isPause = false;
	mLock.unlock();
}
void CameraThread::Close()
{
	mLock.lock();
	isRunning = false;
	mLock.unlock();
}