// ListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SmartFace-WD.h"
#include "ListDialog.h"
#include "afxdialogex.h"


// ListDialog dialog

IMPLEMENT_DYNAMIC(ListDialog, CDialogEx)

ListDialog::ListDialog(CWnd* pParent /*=NULL*/)
	: BaseDialog(ListDialog::IDD, pParent)
{
	mPresenter = new ListPresenter(this);
}

ListDialog::~ListDialog()
{
	delete mPresenter;
}

void ListDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, listData);
	DDX_Control(pDX, IDC_BUTTON1, btnMainMenu);



	//DDX_Control(pDX, IDC_STATIC_TITLE, txtTitle);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, dtCalendar);
	DDX_Control(pDX, IDC_STATIC_TITLE, imgTittle);
}
BOOL ListDialog::OnInitDialog()
{
	BaseDialog::OnInitDialog();

	// Title
	CFont* pFont = CFont::FromHandle((HFONT)afxGlobalData.fontRegular.GetSafeHandle());
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	lf.lfWidth = 10;
	lf.lfHeight = 20;
	CFont font;
	font.CreateFontIndirect(&lf);


	imgTittle.ModifyStyle(0, SS_BITMAP);
	CImage cImage;
	cImage.Load(L"./image/title.jpg");
	imgTittle.SetBitmap(cImage.Detach());
	imgTittle.MoveWindow(20, 10, 440, 70);



	dtCalendar.MoveWindow(140, 100, 200, 30);
	dtCalendar.SetFont(&font);

	listData.MoveWindow(40, 150, 400, 450);

	btnMainMenu.MoveWindow(480 - 20 - 100, 800 - 20 - 100, 100, 100);
	btnMainMenu.SetFont(&font);


	
	listData.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = L"사번";
	listData.InsertColumn(0, &lvColumn);


	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	lvColumn.pszText = L"성명";
	listData.InsertColumn(1, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 40;
	lvColumn.pszText = L"구분";
	listData.InsertColumn(2, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 160;
	lvColumn.pszText = L"시각";
	listData.InsertColumn(3, &lvColumn);


	mPresenter->onInit(getDate());

	font.Detach();
	return TRUE;

}
void ListDialog::addData(ListCheck check)
{
	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	std::wstring s(check.number.begin(), check.number.end());
	lvItem.pszText = (LPWSTR)s.c_str();

	int nItem = listData.InsertItem(&lvItem);
	listData.SetItemText(nItem, 1, Utils::String2CString(check.name));
	listData.SetItemText(nItem, 2, check.type);
	listData.SetItemText(nItem, 3, Utils::String2CString(check.time));

}

BEGIN_MESSAGE_MAP(ListDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ListDialog::OnBtnMainMenuClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &ListDialog::OnNMDblclkList2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &ListDialog::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()


// ListDialog message handlers


void ListDialog::OnBtnMainMenuClick()
{
	this->OnCancel();
}


void ListDialog::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int index = ((NM_LISTVIEW *)pNMHDR)->iItem;

	//CString t(std::to_string(index).c_str());
	//showMessage(t, L"adsfadf");
	ImageDialog dialog(mList[mList.size() - index - 1].image, this);
	dialog.DoModal();
}

void ListDialog::onShowList(std::vector<ListCheck> listCheck)
{
	listData.DeleteAllItems();
	mList = listCheck;
	for (ListCheck l : mList)
	{
		addData(l);
	}
}

void ListDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
	mPresenter->onInit(getDate());

}
std::string ListDialog::getDate()
{
	CTime time;
	dtCalendar.GetTime(time);

	std::stringstream ss;
	std::string m = time.GetMonth() < 10 ? "-0" : "-";
	std::string d = time.GetDay() < 10 ? "-0" : "-";
	ss << time.GetYear() << m << time.GetMonth() << d << time.GetDay();
	return ss.str();
}
