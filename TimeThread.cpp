#include "stdafx.h"
#include "TimeThread.h"


TimeThread::TimeThread(VerifyPresenter * presenter) : mPresenter(presenter)
{

}


TimeThread::~TimeThread()
{
}

BOOL TimeThread::InitInstance()
{
	isRunning = true;
	isPause = false;
	return TRUE;
}
int TimeThread::Run()
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
		std::stringstream ss;
		std::string dt = Utils::getCurrentDatetime();
		std::string d = Utils::getDate(dt);
		std::string t = Utils::getTime(dt);

		ss << d << " " << t;

		mPresenter->showTime(ss.str());
		Sleep(1000);
		
	}
	
	return 0;
}
void TimeThread::Close()
{
	lock.lock();
	isRunning = false;
	lock.unlock();
}
void TimeThread::onPause()
{
	lock.lock();
	isPause = true;
	lock.unlock();
}
void TimeThread::onResume()
{
	lock.lock();
	isPause = false;
	lock.unlock();
}
