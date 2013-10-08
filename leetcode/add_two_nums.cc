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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *dummy = new ListNode(0), *p = dummy;
        int carry = 0;
        do {            
            int sum = carry;
            if (l1 != NULL) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                sum += l2->val;
                l2 = l2->next;
            }
            p->next = new ListNode(sum % 10);            
            carry = sum / 10;            
            p = p->next;
        } 
        while (l1 != NULL || l2 != NULL || carry > 0);
        
        return dummy->next;
    }
};
