#include "stdafx.h"
#include "ProcessingThread.h"



ProcessingThread::ProcessingThread()
{

}
ProcessingThread::~ProcessingThread()
{

}

BOOL ProcessingThread::InitInstance()
{
	isRunning = true;
	isPause = false;
	return TRUE;
}
int ProcessingThread::Run()
{

	while (isRunning)
	{
		lock.lock();
		if (!isRunning)
		{
			lock.unlock();
			break;		
		}
		lock.unlock();

		lock.lock();
		if (isPause)
		{
			lock.unlock();
			continue;
		}
		lock.unlock();

		onProcess();
	}


	return 0;
}
void ProcessingThread::Close()
{
	lock.lock();
	isRunning = false;
	lock.unlock();
}
void ProcessingThread::onPause()
{
	lock.lock();
	isPause = true;
	lock.unlock();
}
void ProcessingThread::onResume()
{
	lock.lock();
	isPause = false;
	lock.unlock();
}
