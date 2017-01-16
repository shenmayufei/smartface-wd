#include "stdafx.h"
#include "Presenter.h"

Presenter::Presenter(Viewer *viewer) : mViewer(viewer)
{
	mBuffer = new SharedImageBuffer();
	mBuffer->add(0, new Buffer<cv::Mat>(24));
}
Presenter::~Presenter()
{
	mBuffer->removeByDeviceNumber(0);
	delete mBuffer;
}
void Presenter::onProcessFrame()
{
	cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
	if (mViewer && frame.data)
	{
		cv::resize(frame, frame, cv::Size(360, 270));
		mViewer->showFrame(frame);
	}
}