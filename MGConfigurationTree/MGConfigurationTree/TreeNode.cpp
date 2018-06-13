#include "stdafx.h"
#include "TreeNode.h"


CTreeNode::CTreeNode()
{
	this->parent = NULL;
	this->child = NULL;
	this->sibling = NULL;
	this->name = "";
	this->space = 0;
}


CTreeNode::~CTreeNode()
{
}

CTreeNode::CTreeNode(CString name, int space, CTreeNode * parent, CTreeNode * child, CTreeNode * sibling)
{
	this->parent = parent;
	this->child = child;
	this->sibling = sibling;
	this->name = name;
	this->space = space;
}

void CTreeNode::AddChild(CTreeNode * c)
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

void CTreeNode::SetParent(CTreeNode * p)
{
	parent = p;
}

void CTreeNode::AddSibling(CTreeNode * s)
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

CTreeNode * CTreeNode::GetChild()
{
	return child;
}

CTreeNode * CTreeNode::GetParent()
{
	return parent;
}

CTreeNode * CTreeNode::GetSibling()
{
	return sibling;
}

int CTreeNode::GetSpace()
{
	return space;
}

CString CTreeNode::GetName()
{
	return name;
}

CString CTreeNode::PrintTree()
{
	CString tmp;
	tmp = GetName() + _T("\n");
	if (child)
	{
		tmp = tmp + child->PrintTree();
		CTreeNode* anotherChild = child->GetSibling();
		while (anotherChild)
		{
			tmp = tmp + anotherChild->PrintTree();
			anotherChild = anotherChild->GetSibling();
		}
	}
	return tmp;
}
