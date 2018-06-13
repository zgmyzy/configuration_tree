#pragma once
#include "TreeNode.h"
#include <string>

class CTreeCtrlMgr
{
public:
	CTreeCtrlMgr();
	~CTreeCtrlMgr();

	CTreeNode* TreeInit(CString strPath);
	void TreeCtrlDisplay(CTreeCtrl* tc, CTreeNode* root, HTREEITEM item);
	void onTest(CTreeCtrl* tc, CString node, HTREEITEM item, int n);
};

