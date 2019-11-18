#pragma once
#include "F:\CIE\Data structure\Project - Github version\DS-PROJECT\project\Rest\Order.h"
#include <tuple>
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	int getCount()
	{
		return count;
	}
	void PrintList()	const
	{
		cout << "\nList has " << count << " nodes";
		cout << "\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(T& val)
	{
		Node<T>* R = new Node<T>(val);
		R->setNext(Head);
		Head = R;
		count++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
		*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (P)
		{
			Head = Head->getNext();
			delete P;
			P = Head;
		}
		count = 0;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd( T &data) {

		if (Head == nullptr) {
			InsertBeg(data);
			return;
		}
		else {
			Node<T> *p = Head;
			while (p->getNext()) {
				p = p->getNext();
			}
			Node<T> *R = new Node<T>(data);
			p->setNext(R);
			count++;
			return;

		}

	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key) {
		Node<T> *p = Head;
		while (p) {
			if (p->getItem() == Key) {
				cout << "Found the element " << Key << endl;
				return true;
			}
			p = p->getNext();
		}
		cout << "\nElement " << Key << " not found" << endl;
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T &value) {
		int occs = 0;
		Node<T> *p = Head;
		while (p) {
			if (p->getItem() == value) {
				occs++;
			}
			p = p->getNext();
		}
		//cout << "\nElement " << value << " was found " << occs << " times" << endl;
		return occs;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst() {
		//	cout << "\nDeleting the first element" << endl;
		if (Head) {
			Node<T> *p = Head->getNext();
			delete Head;
			Head = p;
			count--;
		}
		return;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast() {
		cout << "\nDeleting the last element" << endl;
		if (Head == nullptr) {
			return;
		}
		else if (Head->getNext() == nullptr) {
			DeleteFirst();
			return;
		}
		else {
			Node<T> *p = Head;
			Node<T> *q = p->getNext();
			while (q->getNext()) {
				p = q;
				q = p->getNext();
			}
			delete q;
			p->setNext(nullptr);
			count--;
			return;

		}
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T &value) {
		//cout << "\nDeleting the element " << value << endl;
		if (Head == nullptr) {
			return false;
		}

		if (Head->getItem() == value) {
			DeleteFirst();
			return true;
		}
		Node<T> *p = Head;
		Node<T> *q = p->getNext();

		while (q) {
			if (q->getItem() == value) {
				p->setNext(q->getNext());
				delete q;
				count--;
				return true;
			}
			p = q;
			q = p->getNext();
		}
		return false;
	}


	//overload function for class order for cancellation
	bool DeleteNode(const int &ID) {
		//cout << "\nDeleting the element " << value << endl;
		if (Head == nullptr) {
			return false;
		}

		
		Node<Order> *p = Head;
		Node<Order> *q = p->getNext();

		if (p->getItem().GetID == value) {
			DeleteFirst();
			return true;
		}

		while (q) {
			if (q->getItem().GetID == ID) {
				p->setNext(q->getNext());
				delete q;
				count--;
				return true;
			}
			p = q;
			q = p->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value) {
		cout << "\nDeleting all the elements of value " << value << endl;
		if (Head == nullptr) { return false; }
		bool flag = false;
		while (Head->getItem() == value) {
			DeleteFirst();
			flag = true;
		}
		Node<T>* p = Head;
		while (p->getNext()) {
			if ((p->getNext())->getItem() == value) {
				Node<T>* R = (p->getNext())->getNext();
				delete p->getNext();
				p->setNext(R);
				flag = true;
				count--;

			}
			else {
				p = p->getNext();
			}
		}
		return flag;
	}


	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	Node<T>* getHead() const {
		return Head;
	}

	int getCount() {
		return count;
	}

	void Merge(const LinkedList& L) {
		Node<T> *p = Head;
		if (Head == nullptr) {
			Head = L->getHead();
			return;
		}
		while (p->getNext()) {
			p = p->getNext();
		}
		p->setNext(L->getHead());
		count = count + L->getCount();
		return;
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		cout << "\nReversing the list" << endl;
		if (Head == nullptr) { return; }
		Node<T>* p = Head;
		Node<T>* nextP = Head->getNext();
		Head->setNext(nullptr);
		while (nextP) {
			Node<T>* temp = nextP->getNext();
			nextP->setNext(p);
			p = nextP;
			nextP = temp;
		}
		Head = p;
		return;
	}

	void printkth(int k)
	{
		if (k > (count - 1) || k < 0)
		{
			cout << "Beyond List Length";
		}
		else {
			Node<T>* kptr = Head;

			for (int i = 0; i < k; i++)
			{
				kptr = kptr->getNext();

			}
			cout << kptr->getItem();
		}
	}

	T getkth(int k)
	{
		if (k > (count - 1) || k < 0)
		{
			cout << "Beyond List Length";
		}
		else {
			Node<T>* kptr = Head;

			for (int i = 0; i < k; i++)
			{
				kptr = kptr->getNext();

			}
			return kptr->getItem();
		}
	}


	int issorted()
		// Checks if the list is sorted 1 means descending 2 means ascending -1 means empty list 0 means unsorted 3 means all elements are equal 
		//or list has one element
	{
		bool descending = true;
		bool ascending = true;

		if (Head == NULL)
			return -1; //empty list

		Node<T>* ptr = Head;
		for (ptr = Head; ptr->getNext() != nullptr; ptr = ptr->getNext())
		{
			if (ptr->getItem() < ptr->getNext()->getItem())
				descending = false;
		}

		for (ptr = Head; ptr->getNext() != nullptr; ptr = ptr->getNext())
		{
			if (ptr->getItem() > ptr->getNext()->getItem())
				ascending = false;
		}
		if (descending)
			return 1;

		else if (ascending)
			return 2;
		else if (ascending && descending)
			return 3;

		else
			return 0;
	}

	//overloaded function specified for Order Class
	//sorted is descending
	int issorted()
		// Checks if the list is sorted 1 means descending 2 means ascending -1 means empty list 0 means unsorted 3 means all elements are equal 
		//or list has one element
	{
		bool descending = true;
		bool ascending = true;

		if (Head == NULL)
			return -1; //empty list

		Node<Order>* ptr = Head;
		for (ptr = Head; ptr->getNext() != nullptr; ptr = ptr->getNext())
		{
			if (ptr->getItem().getPriority() < ptr->getNext()->getItem().getPriority())
				descending = false;
		}

		for (ptr = Head; ptr->getNext() != nullptr; ptr = ptr->getNext())
		{
			if (ptr->getItem().getPriority() > ptr->getNext()->getItem().getPriority())
				ascending = false;
		}
		if (descending)
			return 1;

		else if (ascending)
			return -2;
		else if (ascending && descending)
			return 3;

		else
			return 0;
	}



	bool InsertSorted(T data)
	{
		int x = this->issorted();
		if (x <= 0)
		{
			cout << "list is either empty, ascending or unsorted";
			return false;
		}

		if (this->Find(data))
			return false;


		Node <T>* Nn = new Node<T>(data);

		if (Head->getNext() == nullptr) //element
		{
			InsertBeg(data);


			return true;
		}


		Node<T>* ptr = Head;
		if (x == 1) {

			while (ptr->getNext() != nullptr && ptr->getNext()->getItem() > data)
			{
				ptr = ptr->getNext();
			}

			Node<T> *p = ptr->getNext();
			Nn->setNext(p);
			ptr->setNext(Nn);
			return true;
		}

		else if (x == 2) {

			while (ptr->getNext() != nullptr && ptr->getNext()->getItem() < data) {
				ptr = ptr->getNext();
			}

			Node<T> *p = ptr->getNext();
			ptr->setNext(Nn);
			Nn->setNext(p);

			return true;
		}
		count++;
	};

	//overloaded function for class Order
	bool InsertSorted(Order order)
	{
		int x = this->issorted();
		if (x <= 0)
		{
			cout << "list is either empty or unsorted";
			return false;
		}


		Node <Order>* Nn = new Node<Order>;

		if (Head->getNext() == nullptr) //element
		{
			InsertBeg(order);


			return true;
		}


		Node<Order>* ptr = Head;
		if (x == 1) {

			while (ptr->getNext() != nullptr && ptr->getNext()->getItem().getPriority() > order.getPriority())
			{
				ptr = ptr->getNext();
			}

			if ( ptr->getNext->getItem().getPriority() == order.getPriority())
			{
				if (order.getAT() > ptr->getNext->getItem().getAT())
				{
					ptr = ptr->getNext();
				}
			}

			Node<T> *p = ptr->getNext();
			Nn->setNext(p);
			ptr->setNext(Nn);
			return true;
		}

		count++;
	};
	



	Node<T>* removemin() {

		if (Head == nullptr)
			return nullptr
			;

		Node<T>* ptr = Head;
		Node<T>* mini = Head;

		while (ptr != nullptr)
		{
			if (ptr->getItem() < mini->getItem())
				mini = ptr;

			ptr = ptr->getNext();
		}
		//by the end of this loop we should have a pointer mini that points to node with the minimum item

		// Now we should drop the mini node from the list without deleting its pointer because we will return it
		if (mini == Head)
		{
			Head = mini->getNext();
			mini->setNext(nullptr);
		}
		else
		{
			Node <T>* p = Head;
			while (p->getNext()->getItem() != mini->getItem())
			{
				p = p->getNext();
			}
			p->setNext(mini->getNext());
			mini->setNext(nullptr);
		}
		count--;
		return mini;
	}




	LinkedList <T>   CloneList() {

		LinkedList <T>*  NEW = new LinkedList <T>;

		Node<T>*o = this->Head;
		Node<T>*n = new Node<T>(o->getItem());
		NEW->Head = n;
		NEW->count++;
		while (o->getNext() != nullptr)
		{
			n->setNext(new Node<T>(o->getNext()->getItem()));
			n = n->getNext();
			o = o->getNext();
			NEW->count++;
		}
		return *NEW;


	}



	std::tuple<LinkedList<T>*, LinkedList<T>*> SignSplit()
	{
		LinkedList<T> *Lneg = new LinkedList<T>;
		LinkedList<T> *Lpos = new LinkedList<T>;
		T *val = new T;
		if (this->Head != nullptr) {

			Node<T> *p = Head;
			while (p != nullptr) {
				*val = p->getItem();
				if (*val > 0)
				{
					Lpos->InsertEnd(*val);
					p = p->getNext();
					this->DeleteNode(*val);
				}
				else if (*val < 0)
				{
					Lneg->InsertEnd(*val);
					p = p->getNext();
					this->DeleteNode(*val);
				}

				else if (*val == 0) { p = p->getNext(); }

			}

		}


		return  std::make_tuple(Lneg, Lpos);
	}



	LinkedList<T>* sumlist(LinkedList<int>* otherlist) {
		LinkedList<T>* sum = new LinkedList<T>;
		if (this->count != otherlist->count || this->count == 0)
			return NULL;
		Node<T> * tl = this->Head->getNext();
		Node<T> *ol = otherlist->Head->getNext();
		Node<T>*n = new  Node <T>(this->Head->getItem() + otherlist->Head->getItem());
		sum->Head = n;
		Node<T>* s = sum->Head;
		sum->count++;
		while (ol != nullptr)
		{
			s->setNext(new  Node <T>(tl->getItem() + ol->getItem()));
			sum->count++;

			ol = ol->getNext();
			tl = tl->getNext();
			s = s->getNext();


		}
		return sum;
	}


	void Reorderx(T x) {
		Node<T> *p = this->Head;
		T *val = new T;
		for (int i = 0; i <= count; i++) {
			*val = p->getItem();
			if (*val > x)
			{
				p = p->getNext();
				this->DeleteNode(*val);
				InsertEnd(*val);

			}
			else if (*val < x) {
				p = p->getNext();
				this->DeleteNode(*val);
				InsertBeg(*val);
			}


			else { p = p->getNext(); }
		}
	}



	void ShiftLargest() {
		Node <T>*  p = this->Head;
		T *max = new T(p->getItem());

		while (p != nullptr)
		{
			if (p->getItem() > *max)
			{
				*max = p->getItem();
				p = p->getNext();
			}

			else { p = p->getNext(); }

		}
		int x = CountOccurance(*max);

		DeleteNode(*max);
		for (int i = 0; i < x; i++) {
			InsertEnd(*max);
		}

	}



	void removeduplicates() {
		Node<T>* p = this->Head;
		Node<T>*temp = p;

		while (p != nullptr)
		{
			if (CountOccurance(p->getItem()) > 1)
			{
				temp = p;
				p = p->getNext();
				DeleteNode(temp->getItem());
			}
			else { p = p->getNext(); }
		}
	}


	LinkedList<T> MakeDictionary() {
		/*
			LinkedList <T>*  dict = new LinkedList <T>;

			Node<T>*o = this->Head;
			Node<T>*n = new Node<T>({ o->getItem(),  CountOccurance(o->getItem()) });
			dict->Head =  n  ;
			dict->count++;
			while (o->getNext() != nullptr)
			{
				n->setNext(new Node<T>({ o->getNext()->getItem() , CountOccurance(o->getNext()->getItem())) });

				n = n->getNext();
				o = o->getNext();
				dict->count++;
			}
			return *dict;
			*/
	}
};
