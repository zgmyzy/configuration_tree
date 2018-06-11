
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

	m_treeConfig.Create(TVS_HASBUTTONS, CRect(0, 0, 0, 0), this, ID_TREE_CONFIG);
	m_treeConfig.ShowWindow(SW_SHOWNORMAL);

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
	//strPath = _T("D:\\workspace\\MGConfigurationTree\\MGConfigurationTree\\config.txt");
	strPath = _T("E:\\workspace\\tree\\configuration_tree\\MGConfigurationTree\\config.txt");
	TreeInit(strPath);
}




void CMGConfigurationTreeView::TreeInit(CString strPath)
{
	HTREEITEM hTreeRoot;
	HTREEITEM hTreeSub;
	HTREEITEM hTreeSub1;

	//hTreeRoot = m_treeConfig.InsertItem(_T("configure"));


	std::string strPath1 = CStringA(strPath);
	FILE* pFile;
	fopen_s(&pFile, strPath1.c_str(), "r");


	if (pFile == NULL)
	{
		AfxMessageBox(_T("oPENfIL failed"));
	}

	char cData[256];
	TreeNode* tnParent = NULL;
	TreeNode* tnTempParent = new TreeNode();
	while (!feof(pFile))
	{
		memset(cData, 0, 256);
		fgets(cData, 256, pFile);
		CString strData(cData);
		if (strData.GetLength() != 0 && strData != _T("\n"))
		{
			int pos = strData.Find(_T("#"));
			if (0 == pos) continue;
			
			pos = strData.Find(_T("echo"));
			if (-1 != pos) continue;

			pos = strData.Find(_T("exit"));
			if (-1 != pos) continue;
			//CString tmp;
			//tmp.Format(_T("%d", pos));
			//AfxMessageBox(tmp);
			char* c = cData;
			int nSpace = 0;
			while('\0' != *c)
			{
				if (' ' == *c)
				{
					nSpace++;
					c++;
				}
				else
					break;
			}
			TreeNode* newNode = new TreeNode(strData.Mid(nSpace, strData.GetLength()-nSpace-1), nSpace);
			if (!tnParent)
			{
				tnParent = newNode;
			}
			else
			{
				if (nSpace > tnTempParent->GetSpace())
				{
					tnTempParent->AddChild(newNode);
				}
				else if (nSpace == tnTempParent->GetSpace())
				{
					tnTempParent->AddSibling(newNode);
				}
				else
				{
					while ((tnTempParent = tnTempParent->GetParent()) != NULL && nSpace < tnTempParent->GetSpace())
					{}
					if (tnTempParent && nSpace == tnTempParent->GetSpace())
					{
						tnTempParent->AddSibling(newNode);
					}
				}
			}

			tnTempParent = newNode;

		}
		memset(cData, 0, 256);
	}
	fclose(pFile);

	//TreeNode* a = new TreeNode(_T("Tom"));
	//TreeNode* b = new TreeNode(_T("Jony"));
	//TreeNode* c  = new TreeNode(_T("Gray"));
	//TreeNode* d = new TreeNode(_T("Nep"));
	//TreeNode* e = new TreeNode(_T("A"));
	//TreeNode* f = new TreeNode(_T("B"));
	//TreeNode* g = new TreeNode(_T("C"));
	//TreeNode* h = new TreeNode(_T("D"));

	//a->AddChild(b);
	//a->AddChild(c);
	//a->AddChild(d);
	//b->AddChild(e);
	//b->AddChild(f);
	//b->AddChild(g);
	//c->AddChild(h);
	//AfxMessageBox(a->PrintNode());
	//AfxMessageBox(a->PrintTree());



//	m_treeConfig.Expand(hTreeRoot, TVE_EXPAND);
}

