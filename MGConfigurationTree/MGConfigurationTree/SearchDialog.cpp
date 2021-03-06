// SearchDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "MGConfigurationTree.h"
#include "SearchDialog.h"
#include "afxdialogex.h"


// CSearchDialog 对话框

IMPLEMENT_DYNAMIC(CSearchDialog, CDialogEx)

CSearchDialog::CSearchDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
	, m_strSearch(_T(""))
{

}

CSearchDialog::~CSearchDialog()
{
}

void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialogEx)
	ON_BN_CLICKED(IDC_NEXT, &CSearchDialog::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREV, &CSearchDialog::OnBnClickedPrev)
END_MESSAGE_MAP()



void CSearchDialog::SetView(CMGConfigurationTreeView* view)
{
	m_view = view;
}


BOOL CSearchDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE; 
}

void CSearchDialog::OnBnClickedNext()
{
	UpdateData(true);
	//m_view->SearchNext(m_strSearch);
}


void CSearchDialog::OnBnClickedPrev()
{
	UpdateData(true);
	//m_view->SearchPrev(m_strSearch);
}
