/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == NULL) return head;
        ListNode *dummy = new ListNode(-1), *p, *q, *r;
        dummy->next = head;
        p = dummy;
        while (p->next != NULL) {
            q = p->next;
            if (q->next != NULL && q->val == q->next->val) {
                while (q->next != NULL && q->val == q->next->val) {
                    r = q->next;
                    delete(q);
                    q = r;
                }
                p->next = q->next;
                delete(q);
            }
            else 
                p = q;
        }
        head = dummy->next;
        delete(dummy);
        return head;
    }
};
