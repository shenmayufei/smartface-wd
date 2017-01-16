#include "stdafx.h"
#include "CameraVerifyThread.h"




CameraVerifyThread::CameraVerifyThread(VerifyPresenter * presenter)
	: mPresenter(presenter)
{

}
CameraVerifyThread::~CameraVerifyThread()
{

}
void CameraVerifyThread::onProcess()
{
	mPresenter->onVerifyFrame();
}