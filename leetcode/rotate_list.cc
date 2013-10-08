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
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == NULL || k <= 0) return head;
        ListNode *p = head, *q = head;
        int i = 0, len = 0;
        while (q != NULL) {
            q = q->next;
            len++;
        }
        k %= len;
        if (k == 0) return head;
        q = head;
        while (q ->next != NULL && i < k) {
            q = q->next;
            i++;
        }
        while (q->next != NULL) {
            p = p->next;
            q = q->next;
        }
        q->next = head;
        head = p->next;
        p->next = NULL;
        return head;
    }
};
