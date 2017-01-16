// BaseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "BaseDialog.h"
#include "afxdialogex.h"


// BaseDialog dialog

IMPLEMENT_DYNAMIC(BaseDialog, CDialogEx)

BaseDialog::BaseDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
: CDialogEx(nIDTemplate, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
BaseDialog::BaseDialog()
{
}

BaseDialog::~BaseDialog()
{
}
BOOL BaseDialog::PreTranslateMessage(MSG * pMSG)
{
	if (pMSG->message == WM_KEYDOWN
		&& (pMSG->wParam == VK_RETURN || pMSG->wParam == VK_ESCAPE))
	{
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMSG);
}
void BaseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BOOL BaseDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MoveWindow(0, 0, 480, 800);


	//VERIFY(RegisterTouchWindow(TRUE, 0));
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//BOOL BaseDialog::OnTouchInput(CPoint pt, int nInputNumber, int nInputsCount, PTOUCHINPUT pInput)
//{
//	showMessage(L"asdf", L"");
//	return TRUE;
//}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void BaseDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
//BOOL BaseDialog::OnGesturePressAndTap(CPoint ptPress, long lDelta)
//{
//
//	return TRUE;
//}
//BOOL BaseDialog::OnGestureZoom(CPoint ptCenter, long lDelta)
//{
//	return TRUE;
//}
//BOOL BaseDialog::OnGesturePan(CPoint ptFrom, CPoint ptTo)
//{
//	return TRUE;
//}
//BOOL BaseDialog::OnGestureRotate(CPoint ptCenter, double dblAngle)
//{
//	return TRUE;
//}
//BOOL BaseDialog::OnGestureTwoFingerTap(CPoint ptCenter)
//{
//	return TRUE;
//}
void BaseDialog::showMessage(LPCWSTR msg, LPCWSTR caption)
{
	MessageBox(msg, caption);
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR BaseDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void BaseDialog::OnEnSetfocusNumber()
{
	VirtualKeyBoardDialog dialog(this);
	dialog.DoModal();
}
void BaseDialog::OnEnKillfocusNumber()
{

}

BEGIN_MESSAGE_MAP(BaseDialog, CDialogEx)
END_MESSAGE_MAP()


// BaseDialog message handlers
