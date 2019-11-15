#pragma once
template<typename T>
class Stack
{

private:
	T *items;		// Array of stack items
	int      top;                   // Index to top of stack
	const int STACK_SIZE;

public:

	Stack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek

	int count() {
		if (this->top == -1)
			return 0;

		int c = top + 1;

		return c;
	}
	T read_element(int index) {
		if (index < 0 || this->top == -1) {
			cout << "empty stack or invalid index";
			return -1;
		}
		else if (index <= this->count()) {
			T vl = items[index];
			return vl;
		}
	}
	~Stack() {

		delete[] items;
	}
	
};