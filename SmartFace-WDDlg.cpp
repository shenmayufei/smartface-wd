
// SmartFace-WDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "SmartFace-WDDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmartFaceWDDlg dialog



CSmartFaceWDDlg::CSmartFaceWDDlg(CWnd* pParent /*=NULL*/)
	: BaseDialog(CSmartFaceWDDlg::IDD, pParent)
{
}

void CSmartFaceWDDlg::DoDataExchange(CDataExchange* pDX)
{
	BaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, btnVerify);
	DDX_Control(pDX, IDC_BUTTON3, btnEnroll);
	DDX_Control(pDX, IDC_BUTTON4, btnListView);
	DDX_Control(pDX, IDC_BUTTON5, btnSetting);
	DDX_Control(pDX, IDC_BUTTON6, btnClose);
	//DDX_Control(pDX, IDC_STATIC_TITLE, txtTitle);
	DDX_Control(pDX, IDC_STATIC_TITLE, imgTitle);
}

BEGIN_MESSAGE_MAP(CSmartFaceWDDlg, BaseDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CSmartFaceWDDlg::OnBtnEnrollClick)
	ON_BN_CLICKED(IDC_BUTTON6, &CSmartFaceWDDlg::OnBtnCloseClick)
	ON_BN_CLICKED(IDC_BUTTON2, &CSmartFaceWDDlg::OnBtnVerifyClick)
	ON_BN_CLICKED(IDC_BUTTON4, &CSmartFaceWDDlg::OnBtnListClick)
END_MESSAGE_MAP()


// CSmartFaceWDDlg message handlers

BOOL CSmartFaceWDDlg::OnInitDialog()
{
	BaseDialog::OnInitDialog();

	//// Set the icon for this dialog.  The framework does this automatically
	////  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//CFont font;
	//font.CreateFontW(40,                        // nHeight
	//	0,                         // nWidth
	//	0,                         // nEscapement
	//	0,                         // nOrientation
	//	FW_BOLD,                 // nWeight
	//	FALSE,                     // bItalic
	//	FALSE,                     // bUnderline
	//	0,                         // cStrikeOut
	//	ANSI_CHARSET,              // nCharSet
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//	DEFAULT_QUALITY,           // nQuality
	//	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	//	_T("Arial"));                 // lpszFacename


	//GetDlgItem(IDC_STATIC)->SetFont(&font);

	// for this sample here I create a default font with 'italic' attribute set
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

	// Button
	btnEnroll.SetFaceColor(RGB(60, 128, 202), true);
	btnEnroll.SetTextColor(RGB(0, 0, 0));
	btnEnroll.SetFont(&font);
	btnEnroll.MoveWindow(20, 150, 210, 210);
	
	

	
	btnVerify.SetFaceColor(RGB(99, 241, 14), true);
	btnVerify.SetTextColor(RGB(0, 0, 0));
	btnVerify.SetFont(&font);
	btnVerify.MoveWindow(20 + 210 + 20, 150, 210, 210);

	btnListView.SetFaceColor(RGB(82, 179, 77), true);
	btnListView.SetTextColor(RGB(0, 0, 0));
	btnListView.SetFont(&font);
	btnListView.MoveWindow(20, 150 + 210 + 20, 210, 210);

	btnSetting.SetFaceColor(RGB(199, 141, 56), true);
	btnSetting.SetTextColor(RGB(0, 0, 0));
	btnSetting.SetFont(&font);
	btnSetting.MoveWindow(20 + 210 + 20, 150 + 210 + 20, 210, 210);

	


	btnClose.MoveWindow(480 - 20 - 100, 800 - 20 - 100, 100, 100);
	btnClose.SetFont(&font);

	AfxBeginThread(CSmartFaceWDDlg::initThread, this);

	font.Detach();
	return TRUE;  // return TRUE  unless you set the focus to a control
}





void CSmartFaceWDDlg::OnBtnEnrollClick()
{
	EnrollDialog dialog(this);
	dialog.DoModal();
	
	
}


void CSmartFaceWDDlg::OnBtnCloseClick()
{
	this->OnCancel();
}


void CSmartFaceWDDlg::OnBtnVerifyClick()
{
	VerifyDialog dialog(this);
	dialog.DoModal();
}


void CSmartFaceWDDlg::OnBtnListClick()
{
	ListDialog dialog(this);
	dialog.DoModal();
}

// EnrollDialog message handlers
UINT __cdecl CSmartFaceWDDlg::initThread(LPVOID param)
{
	BaseDialog * dialog = (BaseDialog *)param;
	// init engine
	if (FaceEngineBuilder::getEngine(FaceEngineBuilder::SDS).onInit())
	{
		dialog->showMessage(L"INITIALIZE SUCCESSFULLY", L"SDS ENGINE");
	}
	else
	{
		dialog->showMessage(L"INITIALIZE UNSUCCESSFULLY", L"SDS ENGINE");
	}
	DatabaseManager dbManager;
	return 0;
}