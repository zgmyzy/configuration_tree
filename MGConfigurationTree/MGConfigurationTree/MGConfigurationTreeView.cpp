
// MGConfigurationTreeView.cpp : implementation of the CMGConfigurationTreeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MGConfigurationTree.h"
#endif

#include "MGConfigurationTreeDoc.h"
#include "MGConfigurationTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMGConfigurationTreeView

IMPLEMENT_DYNCREATE(CMGConfigurationTreeView, CView)

BEGIN_MESSAGE_MAP(CMGConfigurationTreeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_TEST, &CMGConfigurationTreeView::OnTestForTree)
	ON_NOTIFY(NM_RCLICK, ID_TREE_CONFIG, OnRClickTreeCtrl)
	ON_NOTIFY(NM_DBLCLK, ID_TREE_CONFIG, OnDblClkTreeCtrl)
	ON_COMMAND(ID_RCLICKMENU_EXPANDALL, &CMGConfigurationTreeView::OnRclickmenuExpandall)
	ON_COMMAND(ID_RCLICKMENU_EXPAND, &CMGConfigurationTreeView::OnRclickmenuExpand)
	ON_COMMAND(ID_RCLICKMENU_COLLAPSE, &CMGConfigurationTreeView::OnRclickmenuCollapse)
	ON_COMMAND(ID_RCLICKMENU_COPY, &CMGConfigurationTreeView::OnRclickmenuCopy)
	ON_COMMAND(ID_SEARCH, &CMGConfigurationTreeView::OnSearch)
END_MESSAGE_MAP()

// CMGConfigurationTreeView construction/destruction

DWORD __stdcall ThreadFunc(LPVOID lpParameter)
{
	CSearchDialog dlg;
	dlg.DoModal();
	((CMGConfigurationTreeView*)lpParameter)->OnRclickmenuExpand();
	return NULL;
}

CMGConfigurationTreeView::CMGConfigurationTreeView()
{
	// TODO: add construction code here

}

CMGConfigurationTreeView::~CMGConfigurationTreeView()
{
}

BOOL CMGConfigurationTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMGConfigurationTreeView drawing

void CMGConfigurationTreeView::OnDraw(CDC* /*pDC*/)
{
	CMGConfigurationTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMGConfigurationTreeView printing

BOOL CMGConfigurationTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMGConfigurationTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMGConfigurationTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMGConfigurationTreeView diagnostics

#ifdef _DEBUG
void CMGConfigurationTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CMGConfigurationTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMGConfigurationTreeDoc* CMGConfigurationTreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMGConfigurationTreeDoc)));
	return (CMGConfigurationTreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMGConfigurationTreeView message handlers


int CMGConfigurationTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	m_treeConfig.Create(TVS_HASBUTTONS, CRect(0, 0, 0, 0), this, ID_TREE_CONFIG);
	m_treeConfig.ShowWindow(SW_SHOWNORMAL);
	m_treeConfig.SetIndent(TREECTRL_INDENT);
	return 0;
}


void CMGConfigurationTreeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	CRect rec = CRect(0,0,0,0);
	GetClientRect(&rec);
	m_treeConfig.MoveWindow(rec);

}


void CMGConfigurationTreeView::OnTestForTree()
{
	char path[256];
	memset(path, 0, 256);

	CString strPath;
	//strPath = _T("D:\\workspace\\git_tree\\configuration_tree\\MGConfigurationTree\\TEST.txt");
    strPath = _T("E:\\workspace\\tree\\configuration_tree\\MGConfigurationTree\\TEST.txt");

	CTreeNode* tnTree = m_tcMgr.TreeInit(strPath);
	if (tnTree)
	{
		m_treeConfig.DeleteAllItems();
		m_tcMgr.TreeCtrlDisplay(&m_treeConfig, tnTree, NULL);
		m_tcMgr.TreeCtrlExpand(&m_treeConfig, m_treeConfig.GetRootItem());
		//m_tcMgr.onTest(&m_treeConfig, _T("TEST"), NULL, 20000);
		delete tnTree;
		tnTree = NULL;
	}

}

void CMGConfigurationTreeView::OnRClickTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	CPoint  cp;
	GetCursorPos(&cp);
	m_treeConfig.ScreenToClient(&cp);

	HTREEITEM  item = m_treeConfig.HitTest(cp, NULL);

	if (item != NULL)
	{
		m_treeConfig.SelectItem(item);
		CMenu menu; 
		ClientToScreen(&cp);
		menu.LoadMenu(IDR_MENU_RCLICK);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_TOPALIGN | TPM_LEFTALIGN, cp.x+15, cp.y+10, this, NULL);
	}
}

void CMGConfigurationTreeView::OnDblClkTreeCtrl(NMHDR * pNMHDR, LRESULT * pResult)
{
	PopDialogCopy();
	*pResult = TRUE;
}

void CMGConfigurationTreeView::PopDialogCopy()
{
	CCopyDialog *copyDialog = new CCopyDialog();
	CString temp = m_treeConfig.GetItemText(m_treeConfig.GetSelectedItem());
	HTREEITEM item = m_treeConfig.GetSelectedItem();
	copyDialog->m_str = temp;
	copyDialog->DoModal();
	delete copyDialog;
}




void CMGConfigurationTreeView::OnRclickmenuExpandall()
{
	m_tcMgr.TreeCtrlExpandCollapseAll(&m_treeConfig, m_treeConfig.GetSelectedItem(), true);
}


void CMGConfigurationTreeView::OnRclickmenuExpand()
{
	m_tcMgr.TreeCtrlExpand(&m_treeConfig, m_treeConfig.GetSelectedItem());
}


void CMGConfigurationTreeView::OnRclickmenuCollapse()
{
	m_tcMgr.TreeCtrlExpandCollapseAll(&m_treeConfig, m_treeConfig.GetSelectedItem(), false);
}


void CMGConfigurationTreeView::OnRclickmenuCopy()
{
	PopDialogCopy();
}


void CMGConfigurationTreeView::OnSearch()
{
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, this, 0, &ThreadID);

	CloseHandle(hThread);
}

CTreeCtrlMgr CMGConfigurationTreeView::GetTreeCtrlMgr()
{
	return m_tcMgr;
}

