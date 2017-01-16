#pragma once

// BaseDialog dialog
#include "resource.h"

#include "Utils.h"
#include "VirtualKeyBoardDialog.h"

class BaseDialog : public CDialogEx
{
	DECLARE_DYNAMIC(BaseDialog)

public:
	//BaseDialog(CWnd* pParent = NULL);   // standard constructor
	BaseDialog(UINT nIDTemplate, CWnd *pParent = NULL);
	BaseDialog();
	virtual ~BaseDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_BASE };
	virtual void showMessage(LPCWSTR msg, LPCWSTR caption);
protected:
	HICON m_hIcon;
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMSG);
	afx_msg void OnEnSetfocusNumber();
	afx_msg void OnEnKillfocusNumber();
	//virtual BOOL OnGesturePressAndTap(CPoint ptPress, long lDelta);
	//virtual BOOL OnGestureZoom(CPoint ptCenter, long lDelta);
	//virtual BOOL OnGesturePan(CPoint ptFrom, CPoint ptTo);
	//virtual BOOL OnGestureRotate(CPoint ptCenter, double dblAngle);
	//virtual BOOL OnGestureTwoFingerTap(CPoint ptCenter);
	//virtual BOOL OnTouchInput(CPoint pt, int nInputNumber, int nInputsCount, PTOUCHINPUT pInput);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
