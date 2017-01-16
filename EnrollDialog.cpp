// EnrollDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "EnrollDialog.h"
#include "afxdialogex.h"


// EnrollDialog dialog

IMPLEMENT_DYNAMIC(EnrollDialog, BaseDialog)

EnrollDialog::EnrollDialog(CWnd* pParent /*=NULL*/)
: BaseDialog(EnrollDialog::IDD, pParent)
{
	mPresenter = new EnrollPresenter(this);
}

EnrollDialog::~EnrollDialog()
{
	mPresenter->onExit();
	delete mPresenter;
}

void EnrollDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_IMAGE, mImage);

	DDX_Control(pDX, IDC_BUTTON1, btnEnroll);
	DDX_Control(pDX, IDC_EDIT2, edtName);
	DDX_Control(pDX, IDC_BUTTON2, btnImage1);
	DDX_Control(pDX, IDC_BUTTON3, btnImage2);
	DDX_Control(pDX, IDC_BUTTON7, btnImage3);
	//	DDX_Control(pDX, IDC_BUTTON8, btnDelete);
	DDX_Control(pDX, IDC_BUTTON9, btnMainMenu);
	DDX_Control(pDX, IDC_EDIT1, edtNumber);
	//DDX_Control(pDX, IDC_STATIC_TITLE, txtTitle);
	DDX_Control(pDX, IDC_STATIC_TITLE, imgTitle);
	DDX_Control(pDX, IDC_STATIC_TXT_TITLE, txtTitle);
	DDX_Control(pDX, IDC_STATIC_TXT_NUMBER, txtNumber);
	DDX_Control(pDX, IDC_STATIC_TXT_NAME, txtName);
	DDX_Control(pDX, IDC_BUTTON6, btnDelete);
}
BOOL EnrollDialog::OnInitDialog()
{
	BaseDialog::OnInitDialog();



	mPresenter->onInit();
	mPresenter->onRun();

	// Title
	CFont* pFont = CFont::FromHandle((HFONT)afxGlobalData.fontRegular.GetSafeHandle());
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	lf.lfWidth = 10;
	lf.lfHeight = 20;
	CFont font;
	font.CreateFontIndirect(&lf);


	imgTitle.ModifyStyle(0, SS_BITMAP);
	CImage cImage;
	cImage.Load(L"./image/title.jpg");
	imgTitle.SetBitmap(cImage.Detach());
	imgTitle.MoveWindow(20, 10, 440, 70);


	txtTitle.SetFont(&font);
	txtTitle.MoveWindow(20, 150, 100, 20);

	txtNumber.SetFont(&font);
	txtNumber.MoveWindow(30, 180, 50, 20);
	txtName.SetFont(&font);
	txtName.MoveWindow(30, 220, 50, 20);
	

	edtNumber.MoveWindow(100, 180, 360, 30);
	edtNumber.SetFont(&font);
	edtName.MoveWindow(100, 220, 360, 30);
	edtName.SetFont(&font);

	mImage.MoveWindow(20, 270, 360, 270);

	btnImage1.SetFont(&font);
	btnImage1.MoveWindow(390, 300, 70, 50);

	btnImage2.SetFont(&font);
	btnImage2.MoveWindow(390, 370, 70, 50);

	btnImage3.SetFont(&font);
	btnImage3.MoveWindow(390, 440, 70, 50);

	btnEnroll.SetFont(&font);
	btnEnroll.MoveWindow(120, 560, 100, 70);

	btnDelete.SetFont(&font);
	btnDelete.MoveWindow(260, 560, 100, 70);

	btnMainMenu.MoveWindow(480 - 20 - 100, 800 - 20 - 100, 100, 100);
	btnMainMenu.SetFont(&font);

	font.Detach();

	return TRUE;

}

BEGIN_MESSAGE_MAP(EnrollDialog, BaseDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &EnrollDialog::OnBtnEnrollClick)
	ON_BN_CLICKED(IDC_BUTTON2, &EnrollDialog::OnBtnImage1Click)
	ON_BN_CLICKED(IDC_BUTTON3, &EnrollDialog::OnBtnImage2Click)
	ON_BN_CLICKED(IDC_BUTTON7, &EnrollDialog::OnBtnImage3Click)
	ON_BN_CLICKED(IDC_BUTTON9, &EnrollDialog::OnBtnManMenuClick)
	//ON_EN_SETFOCUS(IDC_EDIT1, &BaseDialog::OnEnSetfocusNumber)
	//ON_EN_SETFOCUS(IDC_EDIT2, &BaseDialog::OnEnSetfocusNumber)
	//ON_EN_KILLFOCUS(IDC_EDIT1, &BaseDialog::OnEnKillfocusNumber)
	//ON_EN_KILLFOCUS(IDC_EDIT2, &BaseDialog::OnEnKillfocusNumber)
END_MESSAGE_MAP()


//// EnrollDialog message handlers
//UINT __cdecl EnrollDialog::myThread(LPVOID param)
//{
//	//CImage cImage;
//	//CStatic * mImage = (CStatic *)param;
//	//cv::VideoCapture cap;
//	//if (!cap.open(0))
//	//{
//	//	std::cout << "could not open camera" << std::endl;
//	//	return -1;
//	//}
//
//	//cv::Mat img;
//	//while (true)
//	//{
//	//	if (cap.read(img))
//	//	{
//	//		if (Utils::Mat2CImage(img, cImage) > -1)
//	//		{
//	//			HBITMAP hold = mImage->SetBitmap(cImage.Detach());
//	//			if (hold)
//	//			{
//	//				VERIFY(::DeleteObject(hold));
//	//			}
//	//			
//	//		}
//	//	}
//
//	//	if (cv::waitKey(10) == 27) break;
//	//}
//	return 0;
//}

void EnrollDialog::OnBtnEnrollClick()
{
	CString cUserName, cUserNumber;
	edtName.GetWindowTextW(cUserName);
	edtNumber.GetWindowTextW(cUserNumber);

	std::string userName = Utils::CString2String(cUserName);
	std::string userNUmber = Utils::CString2String(cUserNumber);


	
	mPresenter->onEnroll(userName, userNUmber);
	
}
void EnrollDialog::showFrame(cv::Mat& frame)
{
	
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

void EnrollDialog::OnBtnImage1Click()
{
	mPresenter->onCapture(1);
}


void EnrollDialog::OnBtnImage2Click()
{
	mPresenter->onCapture(2);
}


void EnrollDialog::OnBtnImage3Click()
{
	mPresenter->onCapture(3);
}


void EnrollDialog::OnBtnManMenuClick()
{
	this->OnCancel();
}


