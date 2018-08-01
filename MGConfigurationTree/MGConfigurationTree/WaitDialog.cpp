// WaitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MGConfigurationTree.h"
#include "WaitDialog.h"
#include "afxdialogex.h"


// CWaitDialog dialog

IMPLEMENT_DYNAMIC(CWaitDialog, CDialogEx)

CWaitDialog::CWaitDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaitDialog::IDD, pParent)
{

}

CWaitDialog::~CWaitDialog()
{
}

void CWaitDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_WAIT, m_progCtrl);
}


BEGIN_MESSAGE_MAP(CWaitDialog, CDialogEx)
END_MESSAGE_MAP()


// CWaitDialog message handlers


BOOL CWaitDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_progCtrl.SetMarquee(TRUE, 30);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CWaitDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}
