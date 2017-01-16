// VirtualKeyBoardDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "VirtualKeyBoardDialog.h"
#include "afxdialogex.h"


// VirtualKeyBoardDialog dialog

IMPLEMENT_DYNAMIC(VirtualKeyBoardDialog, CDialogEx)

VirtualKeyBoardDialog::VirtualKeyBoardDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirtualKeyBoardDialog::IDD, pParent)
{

}

VirtualKeyBoardDialog::~VirtualKeyBoardDialog()
{
}

void VirtualKeyBoardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, btnClose);
	DDX_Control(pDX, IDC_BUTTON2, btn0);
	DDX_Control(pDX, IDC_BUTTON3, btn1);
	DDX_Control(pDX, IDC_BUTTON5, btn2);
	DDX_Control(pDX, IDC_BUTTON7, btn3);
	DDX_Control(pDX, IDC_BUTTON8, btn4);
	DDX_Control(pDX, IDC_BUTTON10, btn5);
	DDX_Control(pDX, IDC_BUTTON11, btn6);
	DDX_Control(pDX, IDC_BUTTON6, btn7);
	DDX_Control(pDX, IDC_BUTTON9, btn8);
	DDX_Control(pDX, IDC_BUTTON12, btn9);
}


BEGIN_MESSAGE_MAP(VirtualKeyBoardDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &VirtualKeyBoardDialog::OnBtnCloseClick)
END_MESSAGE_MAP()


// VirtualKeyBoardDialog message handlers


void VirtualKeyBoardDialog::OnBtnCloseClick()
{
	this->OnCancel();
}

BOOL VirtualKeyBoardDialog::OnInitDialog()
{
	int width = 200;
	int height = 200;
	MoveWindow(480 / 2 - 200 / 2, 800 / 2 - 200 / 2, width, height);

	return TRUE;
}