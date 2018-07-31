// DialogWaiting.cpp : implementation file
//

#include "stdafx.h"
#include "MGConfigurationTree.h"
#include "DialogWaiting.h"
#include "afxdialogex.h"


// CDialogWaiting dialog

IMPLEMENT_DYNAMIC(CDialogWaiting, CDialogEx)

CDialogWaiting::CDialogWaiting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogWaiting::IDD, pParent)
{

}

CDialogWaiting::~CDialogWaiting()
{
}

void CDialogWaiting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GIF, m_GifPic);
}


BEGIN_MESSAGE_MAP(CDialogWaiting, CDialogEx)
END_MESSAGE_MAP()


// CDialogWaiting message handlers


BOOL CDialogWaiting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (m_GifPic.Load(_T("D:\\workspace\\git_tree\\configuration_tree\\MGConfigurationTree\\MGConfigurationTree\\res\\status.gif")))
		//if (m_GifPic.Load(MAKEINTRESOURCE(IDR_GIF_WAITING), _T("Gif")))
	{
		m_GifPic.SetFill();
		m_GifPic.Draw();
	}

	//CFont m_editFont;
	//m_editFont.CreatePointFont(180, _T("Calibri"), NULL);
	//m_Static.SetFont(&m_editFont);


		

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
