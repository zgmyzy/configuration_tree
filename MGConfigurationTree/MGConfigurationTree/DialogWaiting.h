#pragma once
#include "afxwin.h"
#include "PictureEx.h"

// CDialogWaiting dialog

class CDialogWaiting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogWaiting)

public:
	CDialogWaiting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogWaiting();

// Dialog Data
	enum { IDD = IDD_DIALOG_WAITING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CPictureEx m_GifPic;
	virtual BOOL OnInitDialog();
};
