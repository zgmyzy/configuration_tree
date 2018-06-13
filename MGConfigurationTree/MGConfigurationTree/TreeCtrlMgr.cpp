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
		AfxMessageBox(_T("Openf failed"));
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


void CTreeCtrlMgr::TreeCtrlDisplay(CTreeCtrl* tc, CTreeNode* node, HTREEITEM item)
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

	CTreeNode* tnTmp = node->GetChild();

	if (tnTmp)
	{
		TreeCtrlDisplay(tc, tnTmp, hTmp);
	}
	
	tnTmp = node->GetSibling();
	if (tnTmp)
	{
		TreeCtrlDisplay(tc, tnTmp, item);
	}


	tc->Expand(hTmp, TVE_EXPAND);

	return;
}

