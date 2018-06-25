
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
#include "SearchDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DWORD __stdcall ThreadFunc(LPVOID lpParameter)
{
	CSearchDialog* dlg = new CSearchDialog();
	dlg->SetView((CMGConfigurationTreeView*)lpParameter);
	dlg->DoModal();
	dlg = NULL;
	delete dlg;
	return NULL;
}

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
	ON_NOTIFY(NM_DBLCLK, ID_LIST_RES, OnDblclkList)
	ON_COMMAND(ID_RCLICKMENU_EXPANDALL, &CMGConfigurationTreeView::OnRclickmenuExpandall)
	ON_COMMAND(ID_RCLICKMENU_EXPAND, &CMGConfigurationTreeView::OnRclickmenuExpand)
	ON_COMMAND(ID_RCLICKMENU_COLLAPSE, &CMGConfigurationTreeView::OnRclickmenuCollapse)
	ON_COMMAND(ID_RCLICKMENU_COPY, &CMGConfigurationTreeView::OnRclickmenuCopy)
	ON_COMMAND(ID_SEARCH, &CMGConfigurationTreeView::OnSearch)
	ON_BN_CLICKED(ID_BUTTON_N, &CMGConfigurationTreeView::OnClickButtonN)
	ON_BN_CLICKED(ID_BUTTON_P, &CMGConfigurationTreeView::OnClickButtonP)
	ON_BN_CLICKED(ID_BUTTON_A, &CMGConfigurationTreeView::OnClickButtonA)
END_MESSAGE_MAP()

// CMGConfigurationTreeView construction/destruction

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



	m_buttonN.Create(_T("next"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, ID_BUTTON_N);
	m_buttonP.Create(_T("prev"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, ID_BUTTON_P);
	m_buttonA.Create(_T("find all"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 0, 0), this, ID_BUTTON_A);

	m_editFind.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, CRect(0, 60, 100, 110), this, ID_EDIT_TREE_FIND);
	m_treeConfig.Create(TVS_HASBUTTONS, CRect(0, 0, 0, 0), this, ID_TREE_CONFIG);
	m_treeConfig.SetIndent(TREECTRL_INDENT);
	m_treeConfig.ShowWindow(SW_SHOWNORMAL);

	m_listRes.Create(LVS_ALIGNLEFT| LVS_REPORT, CRect(0, 0, 0, 0), this, ID_LIST_RES);

	m_listRes.ShowWindow(SW_HIDE);


	return 0;
}


void CMGConfigurationTreeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
		
	CRect rec = CRect(0, 0, 0, 0);
	GetClientRect(&rec);
	m_treeConfig.MoveWindow(CRect(rec.TopLeft().x, rec.TopLeft().y, rec.BottomRight().x-500, rec.BottomRight().y - 50));

	m_listRes.MoveWindow(CRect(rec.BottomRight().x - 500, rec.TopLeft().y, rec.BottomRight().x, rec.BottomRight().y - 50));
	m_editFind.MoveWindow(CRect(rec.TopLeft().x+10, rec.BottomRight().y - 40, rec.TopLeft().x+ 200, rec.BottomRight().y -10));
	m_buttonN.MoveWindow(CRect(rec.TopLeft().x + 210, rec.BottomRight().y - 40, rec.TopLeft().x + 255, rec.BottomRight().y - 10));
	m_buttonP.MoveWindow(CRect(rec.TopLeft().x + 260, rec.BottomRight().y - 40, rec.TopLeft().x + 305, rec.BottomRight().y - 10));
	m_buttonA.MoveWindow(CRect(rec.TopLeft().x + 310, rec.BottomRight().y - 40, rec.TopLeft().x + 370, rec.BottomRight().y - 10));
	int nColumnCount = m_listRes.GetHeaderCtrl()->GetItemCount();

}

void CMGConfigurationTreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
}


CTreeCtrlMgr CMGConfigurationTreeView::GetTreeCtrlMgr()
{
	return m_tcMgr;
}

void CMGConfigurationTreeView::OnOpenFile(CString strFile)
{
	CTreeNode* tnTree = m_tcMgr.TreeInit(strFile);
	if (!tnTree)
	{
		AfxMessageBox(_T("failed to struct the tree"));
		return;
	}
	listItem.clear();
	strFind = _T("");
	listFindItem.clear();
	if (tnTree)
	{
		m_treeConfig.DeleteAllItems();
		m_tcMgr.TreeCtrlDisplay(&m_treeConfig, tnTree, NULL, &listItem);
		m_tcMgr.TreeCtrlExpand(&m_treeConfig, m_treeConfig.GetRootItem());
		m_tcMgr.TreeDestroy(tnTree);
	}
}

void CMGConfigurationTreeView::OnTestForTree()
{
	char path[256];
	memset(path, 0, 256);

	CString strPath;
	//strPath = _T("D:\\workspace\\git_tree\\configuration_tree\\MGConfigurationTree\\TEST.txt");
    strPath = _T("E:\\workspace\\tree\\configuration_tree\\MGConfigurationTree\\TEST.txt");

	CTreeNode* tnTree = m_tcMgr.TreeInit(strPath);
	if (!tnTree)
	{
		AfxMessageBox(_T("failed to struct the tree"));
		return;
	}
	listItem.clear();
	strFind = _T("");
	listFindItem.clear();
	if (tnTree)
	{
		m_treeConfig.DeleteAllItems();
		m_tcMgr.TreeCtrlDisplay(&m_treeConfig, tnTree, NULL, &listItem);
		m_tcMgr.TreeCtrlExpand(&m_treeConfig, m_treeConfig.GetRootItem());
		//m_tcMgr.onTest(&m_treeConfig, _T("TEST"), NULL, 20000);
		m_tcMgr.TreeDestroy(tnTree);
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
	copyDialog = NULL;
	delete copyDialog;
}


void CMGConfigurationTreeView::OnClickButtonN()
{
	CString tmp;
	m_editFind.GetWindowTextW(tmp);
	m_tcMgr.TreeSearchNextPrev(&m_treeConfig, true, strFind, listItem, tmp);

}

void CMGConfigurationTreeView::OnClickButtonP()
{
	CString tmp;
	m_editFind.GetWindowTextW(tmp);
	m_tcMgr.TreeSearchNextPrev(&m_treeConfig, false, strFind, listItem, tmp);
}

void CMGConfigurationTreeView::OnClickButtonA()
{
	CString tmp;
	m_editFind.GetWindowTextW(tmp);
	m_tcMgr.TreeSearchAll(&m_treeConfig, listItem, listFindItem, strFind, tmp);

	if (listFindItem.empty())
	{
		return;
	}

	m_listRes.DeleteAllItems(); 
	m_listRes.DeleteColumn(0);

	CString col;
	col.Format(_T("Finding %d result \"%s\": "), listFindItem.size(), tmp);

	m_listRes.InsertColumn(0, col, LVCFMT_LEFT, 500, 0);


	int n = 0;
	for (LISTTREE::iterator iter = listFindItem.begin(); iter != listFindItem.end(); iter++, n++)
	{
		m_listRes.InsertItem(n, m_treeConfig.GetItemText(*iter));
	}

	m_listRes.ShowWindow(SW_SHOW);

}


void CMGConfigurationTreeView::OnDblclkList(NMHDR * pNMHDR, LRESULT * pResult)
{
	/*AfxMessageBox(_T("result"));*/
	int nItem = m_listRes.GetNextItem(-1, LVNI_SELECTED);
	if (nItem == -1)
	{
		return;
	}
	LISTTREE::iterator iter = listFindItem.begin();
	for (int n = 0; n < nItem; n++)
	{
		iter++;
	}
	m_tcMgr.TreeCtrlHighlight(&m_treeConfig, *iter);

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
	//hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, this, 0, &ThreadID);

	//CloseHandle(hThread);

}


