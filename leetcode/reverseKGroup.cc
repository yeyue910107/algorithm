#include <iostream>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (head == NULL || head->next == NULL || k == 1) {
            return head;
        }
        ListNode *p = head, *last, *tmp = NULL, *res = head;
        int len = 0;
        while (p != NULL) {
            p = p->next;
            len++;
        }
        p = head;
        last = NULL;
        int i = 0;
        while (len >= k) {
            reverseList(&p, k, &last, &tmp);
            if (i == 0)
                res = tmp;
            len -= k;
            i++;
        }
        return res;
    }
private:
     void reverseList(ListNode **head, const int n, ListNode **last, ListNode **res) {
        ListNode *p = NULL, *q = NULL, *r;
        int i = 0;
        if (*head == NULL || (*head)->next == NULL)
            return;
        r = *head;
        while (i < n) {
            p = q;
            q = r;
            r = r->next;
            q->next = p;
            i++;
        }
        *res = q;
        if (*last != NULL)
            (*last)->next = q;
        *last = *head;
        (*head)->next = r;
        (*head) = r;
    }
};

int main() {
    int s[2] = {1, 2};
    ListNode *head = NULL, *p = head;
    for (int i = 0; i < 2; i++) {
        ListNode *q = new ListNode(s[i]);
        if (head == NULL) {
            head = q;
            p = head;
        }
        else {
            p->next = q;
            p = p->next;
        }
    }
    Solution so;
    ListNode *res = so.reverseKGroup(head, 3);
    p = head;
    while (head != NULL) {
        cout << head->val << endl;
        head = head->next;
        delete(p);
        p = head;
    }
    return 0;
}

