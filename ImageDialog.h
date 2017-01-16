#pragma once
#include "afxwin.h"
#include <string>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "Utils.h"

// ImageDialog dialog

class ImageDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ImageDialog)

public:
	ImageDialog(std::string image, CWnd* pParent = NULL);   // standard constructor
	virtual ~ImageDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMSG);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnCloseClick();
	CStatic mImage;
	std::string mImagePath;
	CButton btnClose;
};
