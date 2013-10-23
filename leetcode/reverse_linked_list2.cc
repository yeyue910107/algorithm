#include <iostream>
#include <assert.h>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (head == NULL || m == n) return head;
        ListNode *dummy = new ListNode(-1), *p, *q, *r;
        dummy->next = head;
        p = dummy;
        int i;
        for (i = 1; i < m; i++)
            p = p->next;
        ListNode *begin = p;
        p = p->next; q = NULL;
        while (p != NULL && i < n) {
            r = q;
            q = p;
            p = p->next;
            q->next = r;
            i++;
        }
        assert(begin->next != NULL && p != NULL);
        begin->next->next = p->next;
        begin->next = p;
        p->next = q;
        head = dummy->next;
        delete(dummy);
        return head;
    }
};

int main() {
    int a[] = {1, 2, 3, 4, 5}, size = sizeof(a) / sizeof(int);
    ListNode *dummy, *head, *p;
    dummy = new ListNode(-1);
    p = dummy;
    for (int i = 0; i < size; i++) {
        ListNode *q = new ListNode(a[i]);
        p->next = q;
        p = q;
    }
    head = dummy->next;
    Solution s;
    ListNode *res = s.reverseBetween(head, 1, 5);
    p = dummy;
    while (p != NULL) {
        head = p->next;
        delete(p);
        p = head;
    }
    return 0;
}
