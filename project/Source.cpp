#include "Rest\Restaurant.h"
#include"Generic_DS/LinkedList.h"
#include"Generic_DS/Queue.h"
#include"Generic_DS/Stack.h"
#include"Generic_DS/BSTree.h"
#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"
#include<iostream>


void removeSpaces(string &line);


int main() {

	Restaurant* pRest = new Restaurant;
	pRest->simpleSimulator();
	//GUIDemo();
	//int pause;
	//cin >> pause;
	
  // testing load from file 


	//****************************************************
	//testing the generic DSs
	/*
	BSTree<int> bst;
	bst.insertBST(8);
	bst.insertBST(13);
	
	bst.insertBST(3);
	bst.insertBST(9);
	bst.insertBST(1);
	bst.insertBST(4);
	bst.inorder_traverse();
	bst.printParents();
	int x;
	cin >> x;
	
	Stack<int>*s = new Stack<int>(50);
	Queue <int>* l = new Queue <int>;
	int *r = new int[6];
	for (int i = 0; i < 6; i++) {
		r[i] = i;
		s->push(r[i]);
		l->enqueue(r[i]);
	}
	cout << "  " << s->count()<< endl;
	cout << "  " << l->count() << endl;
	

	LinkedList<int> L;
	int vals[8] = { 1,2,3,4,5,6,8,9 };
	for (int i = 0; i < 8; i++)
	{
		L.InsertBeg(vals[i]);
	}
	Node <int>* ptr = new Node<int>(7);
	L.InsertSorted(7);
	L.PrintList();
	delete ptr;
	int x;
	cin >> x;
	*/
	
}

int GUIDemo()
{
	GUI gui;
	gui.initSimMode();

	int steps = 1;

	while(true) {
		
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));


		for(int i = 0; i < steps; i++) {
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::ORD_REG));
			gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
			gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		}

		gui.updateInterface();
		gui.handleSimGUIEvents();
		// For Interactive mode
		gui.waitForClick();
		// For step-by-step mode
		gui.sleep(100);
		steps++;
	}

	return 0;
}