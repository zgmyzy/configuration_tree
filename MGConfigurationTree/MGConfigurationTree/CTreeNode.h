#pragma once
#define NULL 0

class TreeNode
{
public:
	TreeNode();
	~TreeNode();
	TreeNode(CString name, int space,  TreeNode* prarent = NULL, TreeNode* child = NULL, TreeNode* sibling = NULL);

	void AddChild(TreeNode* c);
	void SetParent(TreeNode* p);
	void AddSibling(TreeNode* s);

	TreeNode * GetChild();
	TreeNode * GetParent();
	TreeNode * GetSibling();
	int GetSpace();
	CString PrintNode();

	CString PrintTree();

private: 
	TreeNode * child;
	TreeNode * sibling;
	TreeNode * parent;
	CString name;
	int space;
};

