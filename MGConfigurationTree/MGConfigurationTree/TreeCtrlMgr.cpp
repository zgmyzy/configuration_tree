#include "stdafx.h"
#include "TreeCtrlMgr.h"


CTreeCtrlMgr::CTreeCtrlMgr()
{
}


CTreeCtrlMgr::~CTreeCtrlMgr()
{
}


CTreeNode* CTreeCtrlMgr::TreeInit(CString strPath)
{

	std::string strPath1 = CStringA(strPath);
	FILE* pFile;
	fopen_s(&pFile, strPath1.c_str(), "r");


	if (pFile == NULL)
	{
		//CString tmp;
		//tmp.Format(_T("%d", pos));
		//AfxMessageBox(tmp);
		AfxMessageBox(_T("Open file failed"));
		return NULL;
	}

	char cData[256];
	CTreeNode* tnParent = NULL;
	CTreeNode* tnTempParent = new CTreeNode();
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

			char* c = cData;
			int nSpace = 0;
			while ('\0' != *c)
			{
				if (' ' == *c)
				{
					nSpace++;
					c++;
				}
				else
					break;
			}
			CTreeNode* newNode = new CTreeNode(strData.Mid(nSpace, strData.GetLength() - nSpace - 1), nSpace);
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
					{
					}
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
	return tnParent;

}

void CTreeCtrlMgr::onTest(CTreeCtrl* tc, CString node, HTREEITEM item, int n)
{
	HTREEITEM hTmp;
	if (!item)
	{
		hTmp = tc->InsertItem(node);
	}
	else
	{
		hTmp = tc->InsertItem(node, item);

	}
	if (n!=0 && item)
	{
		onTest(tc, node, item, n - 1);
	}
	if (n!=0 && !item)
		onTest(tc, node, hTmp, n - 1);

	tc->Expand(hTmp, TVE_EXPAND);
}


void CTreeCtrlMgr::TreeCtrlDisplay(CTreeCtrl* tc, CTreeNode* node, HTREEITEM item, LISTTREE* listTree)
{
	HTREEITEM hTmp;

	if (item)
	{
		hTmp = tc->InsertItem(node->GetName(), item);
	}
	else
	{
		hTmp = tc->InsertItem(node->GetName());
	}

	listTree->push_back(hTmp);

	CTreeNode* tnTmp = node->GetChild();

	if (tnTmp)
	{
		TreeCtrlDisplay(tc, tnTmp, hTmp, listTree);
	}
	
	tnTmp = node->GetSibling();
	if (tnTmp)
	{
		TreeCtrlDisplay(tc, tnTmp, item, listTree);
	}

	tc->Expand(hTmp, TVE_COLLAPSE);

	return;
}

void CTreeCtrlMgr::TreeCtrlExpand(CTreeCtrl * tc, HTREEITEM item)
{
	tc->Expand(item, TVE_EXPAND);
}

void CTreeCtrlMgr::TreeCtrlExpandCollapseAll(CTreeCtrl* tc, HTREEITEM item, bool expand)
{
	if (!tc->ItemHasChildren(item))
	{
		return;
	}
	HTREEITEM hNextItem = tc->GetChildItem(item);
	while (hNextItem != NULL)
	{
		TreeCtrlExpandCollapseAll(tc, hNextItem, expand);
		hNextItem = tc->GetNextItem(hNextItem, TVGN_NEXT);
	}
	if (expand)
	{
		tc->Expand(item, TVE_EXPAND);
	}
	else
	{
		tc->Expand(item, TVE_COLLAPSE);
	}
	
}


//obsolete
LISTTREE CTreeCtrlMgr::TreeCtrlSearch(CTreeCtrl * tc, HTREEITEM item, CString text)
{
	LISTTREE listItem;
	CString tmp = tc->GetItemText(item);
	//if (item && tmp.Find(text) >= 0)
	//{
	//	listItem.push_back(item);
	//}

	if (item)
		listItem.push_back(item);
	if (!tc->ItemHasChildren(item))
	{
		return listItem;
	}
	HTREEITEM hNextItem = tc->GetChildItem(item);
	while (hNextItem != NULL)
	{
		tmp = tc->GetItemText(hNextItem);
		LISTTREE tmpList = TreeCtrlSearch(tc, hNextItem, text);
		while (!tmpList.empty())
		{
			listItem.push_back(tmpList.front());
			tmpList.pop_front();
		}
		hNextItem = tc->GetNextItem(hNextItem, TVGN_NEXT);
	}
	return listItem;
}

void CTreeCtrlMgr::TreeCtrlHighlight(CTreeCtrl * tc, HTREEITEM item)
{
	tc->SetFocus();
	tc->SelectItem(item);
}

void CTreeCtrlMgr::TreeSearchNextPrev(CTreeCtrl* tc, bool bNext, CString& strFind, LISTTREE listItem, CString strEdit)
{

	bool bFirst = false;

	if (strEdit == "")
	{
		AfxMessageBox(_T("search content is null"));
		return;
	}

	if (strEdit != strFind)
	{
		strFind = strEdit;

		bFirst = true;
	}

	CString tmp;
	if (listItem.empty())
	{
		CString msg;
		msg.Format(_T("empty config tree"), strEdit);
		AfxMessageBox(msg);
		return;
	}

	HTREEITEM treeTmp = tc->GetSelectedItem();
	if (!treeTmp)
	{
		treeTmp = tc->GetRootItem();
	}
	LISTTREE::iterator curItem = listItem.begin();
	for (; curItem != listItem.end(); curItem++)
	{
		if (*curItem == treeTmp)
		{
			break;
		}
	}

	LISTTREE::iterator itmp = curItem;
	if (bFirst)
	{
		tmp = tc->GetItemText(*curItem);

		if (tmp.Find(strFind) >= 0)
		{
			TreeCtrlHighlight(tc, *curItem);
			return;
		}
	}
	do
	{
		if (bNext && ++itmp == listItem.end())
		{
			itmp = listItem.begin();
		}
		else if (!bNext)
		{
			if (itmp == listItem.begin())
				itmp = listItem.end();
			itmp--;
		}
		tmp = tc->GetItemText(*itmp);
		if (tmp.Find(strFind) >= 0)
		{
			TreeCtrlHighlight(tc, *itmp);
			return;
		}
	} while (itmp != curItem);

	if (itmp == curItem)
	{
		CString msg;
		msg.Format(_T("0 mathces %s"), strFind);
		AfxMessageBox(msg);

	}
	return;
}

void CTreeCtrlMgr::TreeSearchAll(CTreeCtrl* tc, LISTTREE listItem, LISTTREE& listFindItem, CString& strFind, CString strEdit)
{
	if (strEdit == "")
	{
		AfxMessageBox(_T("search content is null"));
		return;
	}

	strFind = strEdit;

	listFindItem.clear();
    LISTTREE::iterator iter;

	for (iter = listItem.begin(); iter != listItem.end(); iter++)
	{
		if (tc->GetItemText(*iter).Find(strFind) >= 0)
		{
			listFindItem.push_back(*iter);
		}
	}
	if (listFindItem.empty())
	{
		CString msg;
		msg.Format(_T("0 mathces %s"), strFind);
		AfxMessageBox(msg);
	}
}
