#pragma once

class treeNode
{
private:
	int data;
	treeNode *left;
	treeNode *right;
public:
	treeNode(int val)
	{
		data = val;
		left = right = nullptr;
	}


	void setdata(int d)
	{
		data = d;
	}
	int getdata()
	{
		return data;
	}
	void setleft(treeNode* p)
	{
		left = p;
	}
	treeNode*& getleft()
	{
		return left;
	}
	void setright(treeNode* p)
	{
		right = p;
	}
	treeNode*&getright()
	{
		return right;
	}

};
