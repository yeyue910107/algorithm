#include <iostream>

using namespace std;

enum { STACK_MAX = 1024 };

template <class T>
class Stack {
public:
	void push(T e);
	T pop();
	int count();
	bool is_empty() { return top == -1 ? true : false; }
	Stack() { top = -1; }
	~Stack() {};
private:
	T _array[STACK_MAX];
	int top;
};

template <class T>
class Queue {
public:
	void enqueue(T e);
	T dequeue();
	bool is_empty();
	Queue() {}
	~Queue() {};

private:
	Stack<T> stack1, stack2;
};

template <class T>
void Stack<T>::push(T e) {
	_array[++top] = e;
}

template <class T>
T Stack<T>::pop() {
	return _array[top--];
}

template <class T>
int Stack<T>::count() {
	return (top + 1);
}

template <class T>
void Queue<T>::enqueue(T e) {
	while (!stack2.is_empty())
		stack1.push(stack2.pop());
	stack1.push(e);
}

template <class T>
T Queue<T>::dequeue() {
	if (!stack2.is_empty())
		return stack2.pop();
	while (stack1.count() > 1)
		stack2.push(stack1.pop());
	return stack1.pop();
}

template <class T>
bool Queue<T>::is_empty() {
	return (stack1.is_empty() && stack2.is_empty()) ? true : false;
}