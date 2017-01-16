#pragma once

#include "BaseDialog.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ListCheck.h"
#include <vector>
#include "ListPresenter.h"
#include "ImageDialog.h"
#include "afxdtctl.h"
// ListDialog dialog
class ListPresenter;
class ListDialog : public BaseDialog
{
	DECLARE_DYNAMIC(ListDialog)

public:
	ListDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~ListDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_LIST };

	virtual void onShowList(std::vector<ListCheck> listCheck);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	virtual void addData(ListCheck check);
	ListPresenter * mPresenter;
	std::vector<ListCheck> mList;
	virtual std::string getDate();
public:
	CListCtrl listData;
	CButton btnMainMenu;

	afx_msg void OnBtnMainMenuClick();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	//CStatic txtTitle;
	CDateTimeCtrl dtCalendar;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic imgTittle;
};
