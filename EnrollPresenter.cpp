#include "stdafx.h"
#include "EnrollPresenter.h"


EnrollPresenter::EnrollPresenter(DisplayViewer *viewer)
	: Presenter(viewer)
{
	mDisplay = new CameraDisplayThread(this);
	mCam = new CameraThread(mBuffer);
}


EnrollPresenter::~EnrollPresenter()
{

}

void EnrollPresenter::onEnroll(std::string name, std::string number)
{

	EnrollDialog * dialog = static_cast<EnrollDialog *>(mViewer);
	if (number.empty())
	{
		dialog->showMessage(L"USER NUMBER OR USER NAME IS EMPTY", L"ERROR");
	}
	else if (number.size() != 10)
	{
		dialog->showMessage(L"USER NUMBER MUST BE 10 DIGITS", L"ERROR");
	}
	else
	{
		// query user
		User user;
		user.name = name;
		user.number = number;
		std::vector<User> users = mDBManager.query(name, number);
		if (users.size() > 0)
		{
			user = users[0];
		}
		else
		{
			user.id = -1;
		}

		if (user.id < 0) // insert new user
		{
			if (mDBManager.insert(user) > 0)
			{
				dialog->showMessage(L"INSERT USER SUCCESSFULLY", L"RESULT");
			}
			else
			{
				dialog->showMessage(L"INSERT USER UNSUCCESSFULLY", L"RESULT");
			}
		}
		else // update
		{

			cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
			if (frame.data)
			{
				std::stringstream ss, ssImg;
				ss << USER_DATA_STR << user.id << "_" << user.number;
				ssImg << USER_IMAGE_STR << user.id << "_" << user.number;
				switch (mCaptured)
				{
				case 1:
					ss << "_1.dat";
					ssImg << "_1.bmp";
					user.fet_1 = ss.str();
					user.image_1 = ssImg.str();
					break;
				case 2:
					ss << "_2.dat";
					ssImg << "_2.bmp";
					user.fet_2 = ss.str();
					user.image_2 = ssImg.str();
					break;
				case 3:
					ss << "_3.dat";
					ssImg << "_3.bmp";
					user.fet_3 = ss.str();
					user.image_3 = ssImg.str();
					break;
				default:
					ss << "_1.dat";
					ssImg << "_1.bmp";
					user.fet_1 = ss.str();
					user.image_1 = ssImg.str();
					break;
				}

				if (FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).onEnroll(frame, ss.str())
					&& cv::imwrite(ssImg.str(), frame)
					&& mDBManager.update(user) > 0)
				{
					dialog->showMessage(L"UPDATE USER SUCCESSFULLY", L"RESULT");
				}
				else
				{
					dialog->showMessage(L"UPDATE USER UNSUCCESSFULLY", L"RESULT");
				}
			}


		}
	}


	onResume();
	mCaptured = 0;
}
void EnrollPresenter::onCapture(int cam)
{
	if (mCaptured == cam || mCaptured > 0)
	{
		onResume();
		mCaptured = 0;
	}
	else
	{
		onPause();
		mCaptured = cam;
	}
}
//void EnrollPresenter::onProcessFrame()
//{
//	cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
//	DisplayViewer * viewer = static_cast<DisplayViewer *>(mViewer);
//	if (frame.data && viewer)
//	{
//		cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));
//		viewer->showFrame(frame);
//	}
//
//}
bool EnrollPresenter::onInit()
{
	mCam->CreateThread(CREATE_SUSPENDED);
	mCam->m_bAutoDelete = false;


	mDisplay->CreateThread(CREATE_SUSPENDED);
	mDisplay->m_bAutoDelete = false;

	return true;
}
void EnrollPresenter::onRun()
{
	mCam->ResumeThread();
	mDisplay->ResumeThread();
}
void EnrollPresenter::onPause()
{
	mDisplay->onPause();
	mCam->onPause();

}
void EnrollPresenter::onResume()
{
	mCam->onResume();
	mDisplay->onResume();
}
bool EnrollPresenter::onExit()
{
	WaitForSingleObject(mDisplay, INFINITE);
	mDisplay->Close();
	mDisplay->SuspendThread();
	delete(mDisplay);

	WaitForSingleObject(mCam, INFINITE);
	mCam->Close();
	mCam->SuspendThread();
	delete(mCam);

	return true;
}
//void EnrollPresenter::onProcessFrame()
//{
//	//DisplayViewer *viewer = static_cast<DisplayViewer *>(mViewer);
//	cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
//	if (mViewer && frame.data)
//	{
//		cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));
//		mViewer->showFrame(frame);
//	}
//}