#pragma once
#include <mutex>
#include "VerifyPresenter.h"
class VerifyPresenter;
class TimeThread : public CWinThread
{
public:
	TimeThread(VerifyPresenter * presenter);
	~TimeThread();

	virtual int Run();
	virtual void Close();
	virtual void onPause();
	virtual void onResume();
	virtual BOOL InitInstance();
private:

	bool isRunning;
	bool isPause;
	std::mutex lock;
	VerifyPresenter * mPresenter;

protected:
};

