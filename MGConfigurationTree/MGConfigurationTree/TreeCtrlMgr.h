#pragma once
#include "TreeNode.h"
#include <string>
#include <list>
typedef std::list<HTREEITEM> LISTTREE;


class CTreeCtrlMgr
{
public:
	CTreeCtrlMgr();
	~CTreeCtrlMgr();

	CTreeNode* TreeInit(CString strPath);
	void TreeCtrlDisplay(CTreeCtrl* tc, CTreeNode* root, HTREEITEM item, LISTTREE* listTree);
	void TreeCtrlExpand(CTreeCtrl* tc, HTREEITEM item);
	void TreeCtrlExpandCollapseAll(CTreeCtrl* tc, HTREEITEM item, bool expand);
	void TreeSearchNextPrev(CTreeCtrl* tc, bool bNext, CString &strFind, LISTTREE listItem, CString strEdit);
	void TreeSearchAll(CTreeCtrl* tc, LISTTREE listItem, LISTTREE& listFindItem, CString& strFind, CString strEdit);
	void TreeDestroy(CTreeNode* root);


	LISTTREE TreeCtrlSearch(CTreeCtrl* tc, HTREEITEM item, CString text);

	void TreeCtrlHighlight(CTreeCtrl* tc, HTREEITEM item);

	void onTest(CTreeCtrl* tc, CString node, HTREEITEM item, int n);
};

