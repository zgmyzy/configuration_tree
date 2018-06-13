#pragma once
class CTreeNode
{
public:
	CTreeNode();
	~CTreeNode();

	CTreeNode(CString name, int space, CTreeNode* prarent = NULL, CTreeNode* child = NULL, CTreeNode* sibling = NULL);

	void AddChild(CTreeNode* c);
	void SetParent(CTreeNode* p);
	void AddSibling(CTreeNode* s);

	CTreeNode * GetChild();
	CTreeNode * GetParent();
	CTreeNode * GetSibling();
	int GetSpace();
	CString GetName();

	CString PrintTree();

private:
	CTreeNode * child;
	CTreeNode * sibling;
	CTreeNode * parent;
	CString name;
	int space;
};

