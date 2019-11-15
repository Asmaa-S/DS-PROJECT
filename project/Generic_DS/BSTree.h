#pragma once

#include "treeNode.h"

class BSTree
{
private:
	treeNode* root;

	// Utility Functions - Recursive Functions --------------------------

	// Given functions, WHY "static"?? See the Note below
	static void rec_insertBST(treeNode *& subRoot, int key);
	static void rec_inorder_traverse(treeNode* subRoot);
	static void rec_preorder_traverse(treeNode* subRoot);
	static void rec_postorder_traverse(treeNode* subRoot);
	static void rec_destroy_tree(treeNode *& subRoot);
	static void printParents(treeNode* subROOT);
	static int max_depth(treeNode* subROOT);
	static treeNode* search(treeNode* subROOT, int key);
	static treeNode* autumn(treeNode* subROOT);
	// [NOTE] 
	// The paramter passed to each utility function is named "subRoot" and it should be used as is inside the functions
	// It is a fatal logical mistake to use root (the data member) in place of subRoot inside these functions
	// To prevent developpers from making that mistake unintentionally, we made the functions "static"
	// Now, using "root" instead of the passed "subRoot" by mistake  => syntax error



public:
	BSTree(void);
	~BSTree(void);

	// Public Functions --------------------------

	// Given functions
	void insertBST(int key); // not const
	void inorder_traverse() const;
	void preorder_traverse() const;
	void postorder_traverse() const;
	void destroy_tree(); // not const
	void printParents(); //done
	int max_depth();
	treeNode* search(int key);
	treeNode* autumn();
	// [Note]: in the above public functions:
	// const functions are const because there is no probibility to change 
	// the root (data member) either directly (root = something) 
	// or by indirectly by passing it (by reference) to another function (utility fn here)
};


