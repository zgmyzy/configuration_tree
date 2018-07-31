
// MGConfigurationTreeView.h : interface of the CMGConfigurationTreeView class
//

#pragma once
#include <string>
#include <list>
#include "TreeCtrlMgr.h"
#include "CopyDialog.h"
#include "MGConfigurationTreeDoc.h"
#include "DialogWaiting.h"

#define TREECTRL_INDENT 40

typedef std::list<HTREEITEM> LISTTREE;

class CMGConfigurationTreeView : public CView
{
protected: // create from serialization only
	CMGConfigurationTreeView();
	DECLARE_DYNCREATE(CMGConfigurationTreeView)

// Attributes
public:
	CMGConfigurationTreeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMGConfigurationTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl m_treeConfig;
	CTreeCtrlMgr m_tcMgr;
	CEdit m_editFind;
	CButton m_buttonN;
	CButton m_buttonP;
	CButton m_buttonA;
	CListCtrl m_listRes;
	CProgressCtrl m_pro;
	HANDLE hThread;
	DWORD ThreadID;
	LISTTREE listItem;
	LISTTREE listFindItem;
	CString strFind;

	bool m_bExit;



public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTestForTree();

	void OnRClickTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult); 
	void OnDblClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	void PopDialogCopy();
	void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);

	void OnOpenFile(CString strFile);
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnRclickmenuExpandall();
	afx_msg void OnRclickmenuExpand();
	afx_msg void OnRclickmenuCollapse();
	afx_msg void OnRclickmenuCopy();
	afx_msg void OnSearch();
	afx_msg void OnClickButtonN();
	afx_msg void OnClickButtonP();
	afx_msg void OnClickButtonA();

	CTreeCtrlMgr GetTreeCtrlMgr();
	CProgressCtrl* GetProCtrl();
	bool* GetExit();


	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in MGConfigurationTreeView.cpp
inline CMGConfigurationTreeDoc* CMGConfigurationTreeView::GetDocument() const
   { return reinterpret_cast<CMGConfigurationTreeDoc*>(m_pDocument); }
#endif

