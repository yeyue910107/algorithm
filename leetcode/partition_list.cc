#include <iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
		if (head == NULL)
			return NULL;
        ListNode *p = new ListNode(-1), *q = new ListNode(-1);
        ListNode *pp = p, *qq = q;
        ListNode *r = head;
        while (r != NULL) {
            if (r->val < x) {
				pp->next = r;
				pp = r;
            }
            else {
                qq->next = r;
				qq = r;
            }
			r = r->next;
        }
		pp->next = q->next;
		qq->next = NULL;
		ListNode *tmp = p->next;
		delete p;
		delete q;
		return tmp;
    }
};

int main() {
	int a[6] = {1, 4, 3, 2, 5, 2};
	ListNode *head = NULL, *p;
	for (int i = 0; i < 6; i++) {
		ListNode *q = new ListNode(a[i]);
		if (head == NULL) {
			head = q;
			p = q;
		}
		else {
			p->next = q;
			p = q;
		}
	}
	Solution s;
	head = s.partition(head, 3);

	p = head;
	while (p != NULL) {
		head = p->next;
		delete p;
		p = head;
	}
	return 0;
}
