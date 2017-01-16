#pragma once
//#include "CameraViewer.h"
#include "ProcessingThread.h"
//#include "CameraPresenter.h"
#include "Presenter.h"


class Presenter;
class ProcessingThread;

class CameraDisplayThread : public ProcessingThread
{
public:
	CameraDisplayThread(Presenter * presenter);
	~CameraDisplayThread();

private:
	virtual void onProcess();
	Presenter * mPresenter;
};