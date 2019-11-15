#pragma once
template<class T>
class treeNode
{
private:
	T data;
	treeNode<T> *left;
	treeNode<T> *right;
public:
	treeNode(T val)
	{
		data = val;
		left = right = nullptr;
	}


	void setdata(T d)
	{
		data = d;
	}
	T getdata()
	{
		return data;
	}
	void setleft(treeNode<T>* p)
	{
		left = p;
	}
	treeNode<T>*& getleft()
	{
		return left;
	}
	void setright(treeNode<T>* p)
	{
		right = p;
	}
	treeNode<T>*&getright()
	{
		return right;
	}

};