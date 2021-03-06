// CopyDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "MGConfigurationTree.h"
#include "CopyDialog.h"
#include "afxdialogex.h"


// CCopyDialog 对话框

IMPLEMENT_DYNAMIC(CCopyDialog, CDialogEx)

CCopyDialog::CCopyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COPY, pParent)
	, m_str(_T(""))
{
	//GetDlgItem(IDC_EDIT_COPY)->SetWindowText(_T("DA"));
}

CCopyDialog::~CCopyDialog()
{
}

void CCopyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);}


BEGIN_MESSAGE_MAP(CCopyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CCopyDialog::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CCopyDialog 消息处理程序


void CCopyDialog::OnBnClickedButtonTest()
{
	GetDlgItem(IDC_EDIT_COPY)->SetWindowText(_T("DA"));
}


BOOL CCopyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT_COPY)->SetWindowText(m_str);
	

	return TRUE; 
}


void CCopyDialog::OnBnClickedButtonClose()
{
	OnOK();
}
