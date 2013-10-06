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
    ListNode *swapPairs(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *p = dummy, *q;
        while (p->next != NULL) {
            q = p->next;
            if (q->next == NULL) break;
            p->next = q->next;
            q->next = q->next->next;
            p->next->next = q;
            p = q;
        }
        ListNode *res = dummy->next;
        delete(dummy);
        return dummy->next;
    }
};
