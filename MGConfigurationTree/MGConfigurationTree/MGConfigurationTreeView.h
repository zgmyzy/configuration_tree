
// MGConfigurationTreeView.h : interface of the CMGConfigurationTreeView class
//

#pragma once
#include <string>
#include "TreeCtrlMgr.h"
#include "CopyDialog.h"
#include "SearchDialog.h"

#define TREECTRL_INDENT 40
#define WM_SEARCH_MESSAGE WM_USER+100



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
	HANDLE hThread;
	DWORD ThreadID;


public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTestForTree();

	void OnRClickTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult); 
	void OnDblClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	void PopDialogCopy();
	//static DWORD __stdcall  ThreadFunc(LPVOID lpParameter);

	afx_msg void OnRclickmenuExpandall();
	afx_msg void OnRclickmenuExpand();
	afx_msg void OnRclickmenuCollapse();
	afx_msg void OnRclickmenuCopy();
	afx_msg void OnSearch();

	CTreeCtrlMgr GetTreeCtrlMgr();


};

#ifndef _DEBUG  // debug version in MGConfigurationTreeView.cpp
inline CMGConfigurationTreeDoc* CMGConfigurationTreeView::GetDocument() const
   { return reinterpret_cast<CMGConfigurationTreeDoc*>(m_pDocument); }
#endif

