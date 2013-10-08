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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int size = lists.size();
        if (size == 0) return NULL;
        vector<ListNode *> cur;
        cur.resize(size);
        for (int i = 0; i < size; i++)
            cur[i] = lists[i];
        ListNode *head = new ListNode(-1), *p = head;
        while (true) {
            int _min = find_min(cur);
            if (cur[_min] == NULL)
                break;
            p->next = cur[_min];
            p = p->next;
            cur[_min] = cur[_min]->next;
        }
        return head->next;
    }
private:
    int find_min(vector<ListNode *> &cur) {
        int size = cur.size(), res = 0;
        for (int i = 1; i < size; i++) {
            if (cur[res] == NULL || (cur[i] != NULL && cur[i]->val < cur[res]->val))
                res = i;
        }
        return res;
    }
};
