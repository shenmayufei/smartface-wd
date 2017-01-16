#pragma once
#include "afxwin.h"


// VirtualKeyBoardDialog dialog

class VirtualKeyBoardDialog : public CDialogEx
{
	DECLARE_DYNAMIC(VirtualKeyBoardDialog)

public:
	VirtualKeyBoardDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~VirtualKeyBoardDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_KB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton btnClose;
	afx_msg void OnBtnCloseClick();
	CButton btn0;
	CButton btn1;
	CButton btn2;
	CButton btn3;
	CButton btn4;
	CButton btn5;
	CButton btn6;
	CButton btn7;
	CButton btn8;
	CButton btn9;
};
