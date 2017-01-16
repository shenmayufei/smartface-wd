// VerifyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "VerifyDialog.h"
#include "afxdialogex.h"


// VerifyDialog dialog

IMPLEMENT_DYNAMIC(VerifyDialog, CDialogEx)

VerifyDialog::VerifyDialog(CWnd* pParent /*=NULL*/)
: BaseDialog(VerifyDialog::IDD, pParent)
{
	mPresenter = new VerifyPresenter(this);

}

VerifyDialog::~VerifyDialog()
{
	mPresenter->onExit();

}

void VerifyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_IMAGE, mImage);
	DDX_Control(pDX, IDC_BUTTON1, btnMainMenu);
	DDX_Control(pDX, IDC_BUTTON2, btnStartWorking);
	DDX_Control(pDX, IDC_BUTTON3, btnEndWorking);
	DDX_Control(pDX, IDC_BUTTON7, btnLeave);
	DDX_Control(pDX, IDC_EDIT1, edtNumber);
	//DDX_Control(pDX, IDC_STATIC_TITLE, txtTitle);
	DDX_Control(pDX, IDC_STATIC_TITLE, imgTittle);
	DDX_Control(pDX, IDC_STATIC_TXT_NUMBER, txtNumber);
	DDX_Control(pDX, IDC_STATIC_MESSAGE, txtMessage);

	DDX_Control(pDX, IDC_STATIC_CURRENT, txtTime);
}

void VerifyDialog::showTime(std::string time)
{
	if (txtTime)
	{
		txtTime.SetWindowTextW(Utils::String2CString(time));
	}

}
BOOL VerifyDialog::OnInitDialog()
{
	BaseDialog::OnInitDialog();

	CFont* pFont = CFont::FromHandle((HFONT)afxGlobalData.fontRegular.GetSafeHandle());
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	lf.lfWidth = 10;
	lf.lfHeight = 20;
	CFont font;
	font.CreateFontIndirect(&lf);


	imgTittle.ModifyStyle(0, SS_BITMAP);
	CImage cImage;
	cImage.Load(L"./image/title.jpg");
	imgTittle.SetBitmap(cImage.Detach());
	imgTittle.MoveWindow(20, 10, 440, 70);

	txtTime.SetFont(&font);
	txtTime.MoveWindow(60, 110, 360, 20);

	txtNumber.SetFont(&font);
	txtNumber.MoveWindow(60, 150, 50, 30);

	edtNumber.MoveWindow(110, 150, 310, 30);
	edtNumber.SetFont(&font);

	btnStartWorking.SetFont(&font);
	btnStartWorking.MoveWindow(70, 200, 100, 50);

	btnEndWorking.SetFont(&font);
	btnEndWorking.MoveWindow(190, 200, 100, 50);

	btnLeave.SetFont(&font);
	btnLeave.MoveWindow(310, 200, 100, 50);

	mImage.MoveWindow(60, 270, 360, 270);


	txtMessage.SetFont(&font);
	txtMessage.MoveWindow(60, 560, 360, 60);

	btnMainMenu.MoveWindow(480 - 20 - 100, 800 - 20 - 100, 100, 100);
	btnMainMenu.SetFont(&font);

	mPresenter->onInit();
	mPresenter->onRun();
	mPresenter->onPause();
	font.Detach();



	return TRUE;

}
void VerifyDialog::showFrame(cv::Mat & frame)
{
	//MessageBox(_T("THREAD RUNNING"), _T("caption"), NULL);
	CImage cImage;
	if (Utils::Mat2CImage(frame, cImage) > -1)
	{
		HBITMAP hold = mImage.SetBitmap(cImage.Detach());
		if (hold)
		{
			VERIFY(::DeleteObject(hold));
		}

	}
}

BEGIN_MESSAGE_MAP(VerifyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &VerifyDialog::OnBtnMainMenuClick)
	ON_BN_CLICKED(IDC_BUTTON2, &VerifyDialog::OnBtnStartWorkingClick)
	ON_BN_CLICKED(IDC_BUTTON3, &VerifyDialog::OnBtnEndWorkingClick)
	ON_BN_CLICKED(IDC_BUTTON7, &VerifyDialog::OnBtnLeaveClick)
END_MESSAGE_MAP()


// VerifyDialog message handlers


void VerifyDialog::OnBtnMainMenuClick()
{
	
	this->OnCancel();
}


void VerifyDialog::OnBtnStartWorkingClick()
{
	startVerify(START);
}


void VerifyDialog::OnBtnEndWorkingClick()
{
	startVerify(END);
}


void VerifyDialog::OnBtnLeaveClick()
{
	startVerify(LEAVE);
	
}
void VerifyDialog::showText(LPCTSTR text)
{
	CWnd * label = GetDlgItem(IDC_STATIC_MESSAGE);
	label->SetWindowTextW(text);

	edtNumber.SetWindowTextW(L"");
	mPresenter->onPause();
}
void VerifyDialog::startVerify(int type)
{
	CString cUserNumber;
	edtNumber.GetWindowTextW(cUserNumber);
	std::string userNumber = Utils::CString2String(cUserNumber);

	mPresenter->onStartVerify(type, userNumber);
}