#include <iostream>

using namespace std;

template <class T>
struct Node {
	Node* next;
	T data;
};

template <class T>
class Linkedlist {
public:
	static const int MAX_NODE_NUM = 64;
	void add(T e);
	void reverse();
	bool is_empty();
	void print();
	void reverse_recursive();
	void reverse_stack();
	Linkedlist();
	~Linkedlist() {}
private:
	Node<T>* head;
	Node<T>* reverse_recur(Node<T> *);
};

template <class T>
Linkedlist<T>::Linkedlist() {
	this->head = new Node<T>;
	this->head->next = NULL;
}

template <class T>
void Linkedlist<T>::add(T e) {
	Node<T>* p = head;
	while (p->next != NULL)
		p = p->next;
	Node<T>* node = new Node<T>;
	node->data = e;
	node->next = NULL;
	p->next = node;
}

template <class T>
void Linkedlist<T>::print() {
	Node<T>* p = head;
	while (p->next != NULL && p->next != head) {
		cout << p->next->data << endl;
		p = p->next;
	}
}

template <class T>
bool Linkedlist<T>::is_empty() {
	return (head->next == NULL) ? true : false;
}

template <class T>
void Linkedlist<T>::reverse() {
	Node<T> *p, *q, *r;
	p = this->head;
	if (p->next == NULL)
		return;
	q = p->next;
	r = q->next;
	while (r != NULL) {
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	head->next = q;
}

template <class T>
void Linkedlist<T>::reverse_recursive() {
	reverse_recur(head->next);
}

template <class T>
Node<T>* Linkedlist<T>::reverse_recur(Node<T> *p) {
	if (p->next == NULL) {
		this->head->next = p;
		return p;
	}
	Node<T> *q = reverse_recur(p->next);
	q->next = p;
	p->next = head;
	return p;
}

template <class T>
void Linkedlist<T>::reverse_stack() {
	Node<T> *stack[MAX_NODE_NUM], *p = head->next;
	int top = -1;
	while (p->next != NULL) {
		stack[++top] = p;
		p = p->next;
	}
	stack[++top] = p;
	this->head->next = p;
	while (top > 0) {
		p->next = stack[--top];
		p = p->next;
	}
	p->next = head;
}