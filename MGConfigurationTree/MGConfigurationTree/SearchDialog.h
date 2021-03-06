#pragma once
#include "MGConfigurationTreeView.h"

// CSearchDialog 对话框

class CSearchDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDialog)

public:
	CSearchDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSearchDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSearch;
	afx_msg void OnBnClickedNext();

	void SetView(CMGConfigurationTreeView* view);

private:
	CMGConfigurationTreeView * m_view;


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrev();
};
