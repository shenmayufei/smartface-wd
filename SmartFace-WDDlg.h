
// SmartFace-WDDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "BaseDialog.h"
#include "EnrollDialog.h"
#include "FaceEngineBuilder.h"
#include "VerifyDialog.h"
#include "ListDialog.h"


// CSmartFaceWDDlg dialog
class CSmartFaceWDDlg : public BaseDialog
{
// Construction
public:
	CSmartFaceWDDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SMARTFACEWD_DIALOG };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CMFCButton btnVerify;
	CMFCButton btnEnroll;
	CMFCButton btnListView;
	CMFCButton btnSetting;
	afx_msg void OnBtnEnrollClick();
	CButton btnClose;
	afx_msg void OnBtnCloseClick();
	afx_msg void OnBtnVerifyClick();
	afx_msg void OnBtnListClick();

private:
	static UINT __cdecl initThread(LPVOID param);

public:
	//CStatic txtTitle;
	CStatic imgTitle;
};
