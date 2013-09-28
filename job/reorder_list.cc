#include <iostream>

using namespace std;

struct Node {
	int val;
	Node *next;
	Node() {}
	Node(int val) : val(val), next(NULL) {}
};

int get_len(Node *head) {
	Node *p = head;
	int len = 0;
	while (p != NULL) {
		p = p->next;
		len++;
	}
	return len;
}

Node *reverse(Node *node) {
	Node *p, *q = NULL, *r = node;
	if (node == NULL)
		return NULL;
	while (r->next != NULL) {
		p = q;
		q = r;
		r = r->next;
		q->next = p;
	}
	r->next = q;
	return r;
}

void merge(Node *head, Node *&mid) {
	Node *p = head, *q = mid->next, *tmp1 = NULL, *tmp2 = NULL;
	while (p != mid) {
		tmp1 = p->next;
		p->next = q;
		tmp2 = q->next;
		q->next = tmp1;
		p = tmp1; q = tmp2; mid->next = q;
	}
}

void reorder(Node *head) {
	if (head == NULL || head->next == NULL)
		return;
	int i = 0, len = get_len(head);
	Node *p = head;
	while (i < (len - 1)/2) {
		p = p->next;
		i++;
	}
	p->next = reverse(p->next);
	merge(head, p);
}

int main() {
	int s[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Node *head = NULL, *q;
	for (int i = 0; i < 9; i++) {
		Node *p = new Node(s[i]);
		if (head == NULL) {
			head = p;
			q = p;
		}
		else {
			q->next = p;
			q = p;
		}
	}
	reorder(head);
	q = head;
	while (head != NULL) {
		q = head->next;
		delete(head);
		head = q;
	}
	return 0;
}
