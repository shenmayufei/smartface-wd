#pragma once
//#include "Presenter.h"
#include <mutex>

//class Presenter;

class ProcessingThread : public CWinThread
{
public:
	ProcessingThread();
	~ProcessingThread();
	virtual BOOL InitInstance();
	virtual int Run();
	virtual void Close();
	virtual void onPause();
	virtual void onResume();

private:
	
	bool isRunning;
	bool isPause;
	std::mutex lock;
	virtual void onProcess() = 0;
protected:
	
	//Presenter * mPresenter;
};

