#include "stdafx.h"
#include "CTreeNode.h"


TreeNode::TreeNode()
{
	this->parent = NULL;
	this->child = NULL;
	this->sibling = NULL;
	this->name = "";
	this->space = 0;
}


TreeNode::~TreeNode()
{
}

TreeNode::TreeNode(CString name, int space, TreeNode * parent, TreeNode * child, TreeNode * sibling)
{
	this->parent = parent;
	this->child = child;
	this->sibling = sibling;
	this->name = name;
	this->space = space;
}

void TreeNode::AddChild(TreeNode * c)
{
	if (!c) return;
	c->SetParent(this);
	if (!child) //there is no child
	{
		child = c;  //child to be c
	}
	else
	{
		child->AddSibling(c); // if there is child, add the child's sibling
	}
}

void TreeNode::SetParent(TreeNode * p)
{
	parent = p;
}

void TreeNode::AddSibling(TreeNode * s)
{
	if (!s) return;
	s->SetParent(this->GetParent());

	if (!sibling)
	{
		sibling = s;
	}
	else
	{
		sibling->AddSibling(s);  //add to sibling's sibling
	}
}

TreeNode * TreeNode::GetChild()
{
	return child;
}

TreeNode * TreeNode::GetParent()
{
	return parent;
}

TreeNode * TreeNode::GetSibling()
{
	return sibling;
}

int TreeNode::GetSpace()
{
	return space;
}

CString TreeNode::PrintNode()
{
	return name;
}

CString TreeNode::PrintTree()
{
	CString tmp;
	tmp = PrintNode() + _T("\n");
	if (child)
	{
		tmp = tmp + child->PrintTree();
		TreeNode* anotherChild = child->GetSibling();
		while (anotherChild)
		{
			tmp = tmp + anotherChild->PrintTree();
			anotherChild = anotherChild->GetSibling();
		}
	}
	return tmp;
}
