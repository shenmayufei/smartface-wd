// ImageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "ImageDialog.h"
#include "afxdialogex.h"


// ImageDialog dialog

IMPLEMENT_DYNAMIC(ImageDialog, CDialogEx)

ImageDialog::ImageDialog(std::string image, CWnd* pParent /*=NULL*/)
: CDialogEx(ImageDialog::IDD, pParent), mImagePath(image)
{

}

ImageDialog::~ImageDialog()
{
}

void ImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, mImage);
	DDX_Control(pDX, IDC_BUTTON1, btnClose);
}

BOOL ImageDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO: Add extra initialization here
	
	MoveWindow(480/2 - 100 , 800/2 - 100, 200, 200);

	mImage.MoveWindow(20, 10, 160, 120);

	CImage cImage;
	cv::Mat frame = cv::imread(mImagePath);
	if (frame.data)
	{
		cv::resize(frame, frame, cv::Size(160, 120));
		if (Utils::Mat2CImage(frame, cImage) > -1)
		{
			HBITMAP hold = mImage.SetBitmap(cImage.Detach());
			if (hold)
			{
				VERIFY(::DeleteObject(hold));
			}

		}
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}
BOOL ImageDialog::PreTranslateMessage(MSG * pMSG)
{
	if (pMSG->message == WM_KEYDOWN
		&& (pMSG->wParam == VK_RETURN || pMSG->wParam == VK_ESCAPE))
	{
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMSG);
}
BEGIN_MESSAGE_MAP(ImageDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ImageDialog::OnBtnCloseClick)
END_MESSAGE_MAP()


// ImageDialog message handlers


void ImageDialog::OnBtnCloseClick()
{
	this->OnCancel();
}
