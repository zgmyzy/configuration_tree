#pragma once
#include "afxcmn.h"
#include "resource.h"

// CWaitDialog dialog

class CWaitDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CWaitDialog)

public:
	CWaitDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaitDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progCtrl;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
