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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (head == NULL)
            return NULL;
        ListNode* p = head, *q = head;
        for (int i = 0; i < n; i++) {
            p = p->next;
        }
        if (p == NULL) {
            return head->next;
        }
        while (p->next != NULL) {
            q = q->next;
            p = p->next;
        }
        ListNode* tmp = q->next;
        q->next = tmp->next;
        delete(tmp);
        return head;
        
    }
};
