
#pragma once

#include "BSTree.h"

#include <iostream>
using namespace std;

// Utility Functions - Recursive Functions --------------------------

// Given functions

// Insert an integer key in a binary search tree.
// [Note]: subRoot is passed by ref because 
//         the new node may be inserted in the subRoot (if subRoot is empty nullptr)
void BSTree::rec_insertBST(treeNode *& subRoot, int key)
{
	if (subRoot == nullptr)
		subRoot = new treeNode(key); // this line is why we pass subRoot by reference (subRoot = something)
	else if (subRoot->getdata() < key)
	{

		// ***   VERY IMPORTANT NOTE  *** //

		// rec_insertBST takes subRoot param (by reference)
		// Here we need to pass the right pointer that is returned from subRoot->getright() function
		//We have two case here:
		// 1- if Node::getright() is declared as  Node* Node::getright();			
		//		i.e. it returns "right" pointer (return by value)
		//		in this case, the returned pointer is called rvale (right-value)
		//		rvalue in C++ cannot be used at the left of assignment statement
		//		and cannot be passed by ref.
		//
		//2- if Node::getright() is declared as  Node*& Node::getright();
		//		i.e. it returns an alias to "right" pointer (return by ref)
		//		in this case, the returned pointer is called lvale (left-value)
		//		lvalue in C++ CAN be used at the left of assignment statement
		//		and CAN be passed by ref.

		// --> if getright() didn't return a reference, this line would give Syntax Error : because we cannot pass rvalue to by-reference parameter
		rec_insertBST(subRoot->getright(), key);


		//IF for any reason, getright in your code MUST return by value 
		// So the above call rec_insertBST(subRoot->getright(), key); would give an error because subRoot->getright() is rvalue
		// In this case you need to do the folowing:
		// 1- store right pointer it in temp, 
		// 2- pass the temp to the function, 
		// 3- set the right of subRoot with this temp (after calling the fn because it may be changed inside it - by ref)
		//Here is the code in this case to perform the same task
		/*
		Node * sub_right = subRoot->getright();
		rec_insertBST(sub_right, key);
		subRoot->setright(sub_right);
		*/


		// Remember: rvalue is some expression that is not stored in memory with a specific name
		// hence, you can't reach it by a name beyond the line that contains it 
		// like (x + 9): x is stored in memory, but (x + 9) returns a temp result that is not stored in memory with a name
		// same case for: subRoot->getright() --> if it returns an rvalue (or temp result without a name) of the "right"
	}
	else
	{
		// recursive call on left
		rec_insertBST(subRoot->getleft(), key);
	}
}

//* print the tree with inorder traversal.
void BSTree::rec_inorder_traverse(treeNode* subRoot)
{
	if (subRoot == nullptr) return;
	rec_inorder_traverse(subRoot->getleft());
	cout << subRoot->getdata() << " ";
	rec_inorder_traverse(subRoot->getright());
}

//* print the tree with preorder traversal.
void BSTree::rec_preorder_traverse(treeNode* subRoot)
{
	if (subRoot == nullptr) return;
	cout << subRoot->getdata() << "  ";
	rec_preorder_traverse(subRoot->getleft());
	rec_preorder_traverse(subRoot->getright());
}

//* print the tree with postorder traversal.
void BSTree::rec_postorder_traverse(treeNode* subRoot)
{
	if (subRoot == nullptr) return;
	rec_postorder_traverse(subRoot->getleft());
	rec_postorder_traverse(subRoot->getright());
	cout << subRoot->getdata() << "  ";
}

//* Deletes all the nodes in the tree.
// [Note]: subRoot is passed by ref because 
//         after deleting subRoot node we will make it point to nullptr (change subRoot)
void BSTree::rec_destroy_tree(treeNode *& subRoot)
{
	if (subRoot != nullptr)
	{
		// recursive call on left
		rec_destroy_tree(subRoot->getleft());

		// recursive call on right
		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
	}
}

void BSTree::printParents(treeNode* subROOT)
{

	if (subROOT == nullptr || (subROOT->getleft() == nullptr && subROOT->getright() == nullptr))
	{
		return;
	}

	else {
		//int x = subROOT->getdata(); Node* r = subROOT->getleft(); Node* l = subROOT->getleft();
		cout << endl << subROOT->getdata() << endl;
		printParents(subROOT->getright());
		printParents(subROOT->getleft());
	}
}

int BSTree::max_depth(treeNode * subROOT)
{
	int c = 0;
	if (subROOT == nullptr) {
		return 0;
	}

	int leftDepth = max_depth(subROOT->getleft());
	int rightDepth = max_depth(subROOT->getright());

	if (leftDepth > rightDepth)
		return(leftDepth + 1);
	else return(leftDepth + 1);
}

treeNode * BSTree::search(treeNode * subROOT, int key)
{
	if (subROOT == nullptr || subROOT->getdata() == key)
		return subROOT;

	// Key is greater than root's key 
	if (subROOT->getdata() < key)
		return search(subROOT->getright(), key);

	// Key is smaller than root's key 
	return search(subROOT->getleft(), key);
}

treeNode* BSTree::autumn(treeNode * subROOT)
{
	if (subROOT == nullptr)
		return nullptr;

	if (subROOT->getleft() == nullptr && subROOT->getright() == nullptr) {
		treeNode* p = subROOT;
		delete(p);
		return nullptr;
	}

	// Else recursively delete in left and right 
	// subtrees. 
	subROOT->getleft() = autumn(subROOT->getleft());
	subROOT->getright() = autumn(subROOT->getright());
	return subROOT;

}


BSTree::BSTree()
{
	root = nullptr;
}


BSTree::~BSTree()
{
	destroy_tree();
}

// Public Functions ---------------------------------

// Given functions
void BSTree::insertBST(int key) // not const
{
	// not const because rec_insertBST takes the root by reference, so may change it
	rec_insertBST(root, key);
}
void BSTree::inorder_traverse() const
{
	rec_inorder_traverse(root);
}
void BSTree::preorder_traverse() const
{
	rec_preorder_traverse(root);
}
void BSTree::postorder_traverse() const
{
	rec_postorder_traverse(root);
}
void BSTree::destroy_tree() // not const
{
	// not const because rec_destroy_tree takes the root by reference, so may change it
	rec_destroy_tree(root);
}

void BSTree::printParents()
{
	printParents(root);
}

int BSTree::max_depth()
{
	return max_depth(root);
}

treeNode * BSTree::search(int key)
{
	return search(root, key);
}

treeNode* BSTree::autumn()
{
	return autumn(root);

}

