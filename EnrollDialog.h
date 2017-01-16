#pragma once

#include "BaseDialog.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include "afxwin.h"

// EnrollDialog dialog
//#include "CameraViewer.h"
#include "DisplayViewer.h"
#include "EnrollPresenter.h"

class EnrollPresenter;

class EnrollDialog : public BaseDialog, public DisplayViewer
{
	DECLARE_DYNAMIC(EnrollDialog)

public:
	EnrollDialog(CWnd* pParent = NULL);   // standard constructor
	~EnrollDialog();
	//
// Dialog Data
	enum { IDD = IDD_DIALOG_ENROLL };
	virtual void showFrame(cv::Mat& frame);
	CButton btnEnroll;
	afx_msg void OnBtnEnrollClick();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
private:
	CStatic mImage;
	
	EnrollPresenter * mPresenter;
	DECLARE_MESSAGE_MAP()

public:
	CEdit edtName;
	CButton btnImage1;
	CButton btnImage2;
	CButton btnImage3;
	//CButton btnDelete;
	afx_msg void OnBtnImage1Click();
	afx_msg void OnBtnImage2Click();
	afx_msg void OnBtnImage3Click();
	CButton btnMainMenu;
	afx_msg void OnBtnManMenuClick();
	CEdit edtNumber;
	//CStatic txtTitle;
	
	CStatic imgTitle;
	CStatic txtTitle;
	CStatic txtNumber;
	CStatic txtName;
	CButton btnDelete;
};
