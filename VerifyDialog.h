#pragma once

#include "BaseDialog.h"
#include "VerifyViewer.h"
#include "VerifyPresenter.h"
#include "afxwin.h"
#include <mmsystem.h>


// VerifyDialog dialog
class VerifyPresenter;

class VerifyDialog : public BaseDialog, public VerifyViewer
{
	DECLARE_DYNAMIC(VerifyDialog)

public:
	VerifyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~VerifyDialog();

	virtual BOOL OnInitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_VERIFY };
	void showFrame(cv::Mat& frame);
	virtual void showText(LPCTSTR text);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void showTime(std::string time);
	DECLARE_MESSAGE_MAP()
private:
	CStatic mImage;
	VerifyPresenter *mPresenter;
	
	virtual void startVerify(int type);
	
public:
	CButton btnMainMenu;
	afx_msg void OnBtnMainMenuClick();
	CButton btnStartWorking;
	CButton btnEndWorking;
	CButton btnLeave;
	afx_msg void OnBtnStartWorkingClick();
	afx_msg void OnBtnEndWorkingClick();
	afx_msg void OnBtnLeaveClick();
	CEdit edtNumber;
	//CStatic txtTitle;
	CStatic imgTittle;
	CStatic txtNumber;
	CStatic txtMessage;

	CStatic txtTime;

	
};
