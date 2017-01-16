#include "stdafx.h"
#include "CameraDisplayThread.h"



CameraDisplayThread::CameraDisplayThread(Presenter * presenter)
	: mPresenter(presenter)
{

}
CameraDisplayThread::~CameraDisplayThread()
{

}
void CameraDisplayThread::onProcess()
{
	mPresenter->onProcessFrame();
}