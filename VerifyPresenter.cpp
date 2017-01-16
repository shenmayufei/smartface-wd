#include "stdafx.h"
#include "VerifyPresenter.h"


VerifyPresenter::VerifyPresenter(VerifyViewer *viewer) 
	: Presenter(viewer)
{
	mVerifyThread = new CameraVerifyThread(this);
	mDisplay = new CameraDisplayThread(this);
	mCam = new CameraThread(mBuffer);
	tThread = new TimeThread(this);
}


VerifyPresenter::~VerifyPresenter()
{
}
bool VerifyPresenter::onInit()
{
	mCam->CreateThread(CREATE_SUSPENDED);
	mCam->m_bAutoDelete = false;


	mDisplay->CreateThread(CREATE_SUSPENDED);
	mDisplay->m_bAutoDelete = false;


	

	mVerifyThread->CreateThread(CREATE_SUSPENDED);
	mVerifyThread->m_bAutoDelete = false;

	tThread->CreateThread(CREATE_SUSPENDED);
	tThread->m_bAutoDelete = false;

	// query user
	mUsers = mDBManager.query(-1);

	return true;
}
void VerifyPresenter::onRun()
{
	mCam->ResumeThread();
	mDisplay->ResumeThread();

	mVerifyThread->ResumeThread();

	tThread->ResumeThread();
}
void VerifyPresenter::onPause()
{
	//mDisplay->onPause();
	//mCam->onPause();
	mVerifyThread->onPause();
}
void VerifyPresenter::onResume()
{
	//mCam->onResume();
	//mDisplay->onResume();
	mVerifyThread->onResume();
}
bool VerifyPresenter::onExit()
{
	WaitForSingleObject(mDisplay, INFINITE);
	mDisplay->Close();
	mDisplay->SuspendThread();
	delete(mDisplay);

	WaitForSingleObject(mCam, INFINITE);
	mCam->Close();
	mCam->SuspendThread();
	delete(mCam);

	WaitForSingleObject(mVerifyThread, INFINITE);
	mVerifyThread->Close();
	mVerifyThread->SuspendThread();
	delete(mVerifyThread);

	WaitForSingleObject(tThread, INFINITE);
	tThread->Close();
	tThread->SuspendThread();
	delete(tThread);

	return true;
}
void VerifyPresenter::showTime(std::string time)
{
	VerifyViewer * dialog = dynamic_cast<VerifyViewer *>(mViewer);
	if (dialog)
	{
		dialog->showTime(time);
	}
}
//void VerifyPresenter::onProcessFrame()
//{
//	//VerifyViewer *viewer = static_cast<VerifyViewer *>(mViewer);
//	cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
//	if (mViewer && frame.data)
//	{
//		cv::resize(frame, frame, cv::Size(frame.cols / 2, frame.rows / 2));
//		mViewer->showFrame(frame);
//	}
//}
void VerifyPresenter::onVerifyFrame()
{
	
	cv::Mat frame = mBuffer->getByDeviceNumber(0)->get();
	if (frame.data && FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).isFace(frame))
	{
		VerifyViewer * dialog = dynamic_cast<VerifyViewer *>(mViewer);
		std::vector<User>::iterator begin = mUsers.begin();
		std::vector<User>::iterator end = mUsers.end();
		bool rs = false;
		for (std::vector<User>::iterator it = begin; it != end; ++it)
		{
			rs = false;
			if (FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).onMatching(frame, (*it).fet_1) > MATCHING_THRESHOLD)
			{
				rs = true;
			}
			else if (FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).onMatching(frame, (*it).fet_2) > MATCHING_THRESHOLD)
			{
				rs = true;

			}
			else if (FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).onMatching(frame, (*it).fet_3) > MATCHING_THRESHOLD)
			{
				rs = true;

			}
			if (rs)
			{
				Sleep(500);

				switch (mNum)
				{
				case START:
					Utils::playSound(_T("./audio/StartWorking Checking.wav"));
					break;
				case END:
					Utils::playSound(_T("./audio/EndWorking Checking.wav"));
					break;
				case LEAVE:
					Utils::playSound(_T("./audio/Leave Checking.wav"));
					break;
				default:
					continue;
				}

				// insert db

				User user = *it;

				std::string dt = Utils::getCurrentDatetime();
				std::string d = Utils::getDate(dt);
				std::string t = Utils::getTime(dt);

				std::stringstream ss;
				ss << USER_HISTORY_STR << user.id << "_" << user.number << "_" << mNum << "_" << Utils::formatDateTime(dt) << ".bmp";
				cv::imwrite(ss.str(), frame);
				List l;
				l.user_id = user.id;
				l.type = mNum;
				l.image = ss.str();
				l.date = d;
				l.time = t;
				mDBManager.insertList(l);

				if (dialog)
				{
					CString t = CString((*it).number.c_str());
					t.Format(_T("%s"), _T("인증되었습니다"));
					dialog->showText(t);
					Sleep(3000);
					dialog->showText(_T(""));
				}

				break;
			}
		}
		if (!rs && (mNum == START || mNum == END || mNum == LEAVE))
		{
			Utils::playSound(_T("./audio/Enroll User Unsuccessfully.wav"));
			VerifyDialog * dialogV = dynamic_cast<VerifyDialog *>(mViewer);
			if (dialogV)
			{
				dialogV->showMessage(L"사진정보가 등록되지 않은 사용자입니다.", L"ERROR");
			}
			Sleep(3000);
			dialog->showText(_T(""));
		}

	}
}

void VerifyPresenter::onStartVerify(int num, std::string number)
{
	switch (num)
	{
	case START:
		Utils::playSound(_T("./audio/StartWorking.wav"));
		break;
	case END:
		Utils::playSound(_T("./audio/EndWorking.wav"));
		break;
	case LEAVE:
		Utils::playSound(_T("./audio/Leave.wav"));
		break;
	}

	if (number.empty())
	{
		VerifyDialog * dialog = dynamic_cast<VerifyDialog *>(mViewer);
		if (dialog)
		{
			dialog->showMessage(L"USER NUMBER IS EMPTY", L"ERROR");
		}
	}
	else
	{
		mUsers = mDBManager.query(number);
		if (mUsers.size() == 0)
		{
			Utils::playSound(_T("./audio/Enroll Number Unsuccessfully.wav"));
			VerifyDialog * dialog = dynamic_cast<VerifyDialog *>(mViewer);
			if (dialog)
			{
				dialog->showMessage(L"등록되지 않은 사번입니다.", L"ERROR");
				Sleep(3000);
				dialog->showText(_T(""));
			}	

		}
		else
		{
			mNum = num;
			onResume();
		}

	}

}