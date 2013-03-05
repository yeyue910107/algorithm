#include <iostream>
#define MAX 64
using namespace std;

typedef struct node{
	struct node* next;
	int data;
}LNode, *Linklist;

void create_list(Linklist &list, const int n);
void josephu(Linklist &list, int n, int m, int k);

int main(void) {
	int n = 8, m = 4, k = 3;
	Linklist list = NULL;
	create_list(list, n);
	josephu(list, n, m, k);
}

void create_list(Linklist &list, const int n) {
	int i;
	Linklist p, q;
	//list = (Linklist)malloc(sizeof(LNode));

	for (i = 0, p = list; i < n; i++) {
		p = (Linklist)malloc(sizeof(LNode));
		p->data = i + 1;
		p->next = NULL;
		if (list == NULL)
			list = p;
		else
			q->next = p;
		q = p;
	}
	p->next = list;
}

void josephu(Linklist &list, int n, int m, int k) {
	int i;
	Linklist p, q;

	for (i = 1, p = list; i < k - 1; i++)
		p = p->next;
	while (n > 0) {
		for (i = 0; i < m - 1; i++)
			p = p->next;
		q = p->next;
		p->next = q->next;
		printf("%d\n", q->data);
		free(q);
		n--;
	}
}