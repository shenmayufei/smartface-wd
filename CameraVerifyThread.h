#pragma once
#include "VerifyPresenter.h"
#include "ProcessingThread.h"

class ProcessingThread;
class VerifyPresenter;
class CameraVerifyThread : public ProcessingThread
{
public:
	CameraVerifyThread(VerifyPresenter * presenter);
	~CameraVerifyThread();

private:
	virtual void onProcess();
	VerifyPresenter * mPresenter;
};

