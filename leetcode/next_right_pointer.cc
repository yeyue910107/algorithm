#include <iostream>
#include <queue>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void _connect(TreeLinkNode *root) {
        if (root == NULL)
            return;
        queue<TreeLinkNode *> q;
        TreeLinkNode *end = root, *prev = NULL;
        q.push(root);
        while (!q.empty()) {
            TreeLinkNode *cur = q.front();
            q.pop();
            if (cur == end) {
                cur->next = NULL;
                if (cur->left == NULL && cur->right == NULL)
                    end = prev;
                else if (cur->right != NULL) end = cur->right;
                else end = cur->left;
            }
            if (cur->left != NULL) {
                if (prev != NULL)
                    prev->next = cur->left;
                prev = cur->left;
                q.push(cur->left);
            }
            if (cur->right != NULL) {
                if (prev != NULL)
                    prev->next = cur->right;
                prev = cur->right;
                q.push(cur->right);
            }
        }
        if (end != NULL)
            end->next = NULL;
    }

    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return ;
        root->next = NULL;
        TreeLinkNode *prev = root, *last = root, *head, *p;
        
        while (last != NULL) {
            head = NULL;
            p = last;
            while (p != NULL) {
                if (p->left != NULL) {
                    if (head == NULL) {
                        head = p->left;
                        prev = head;
                    }
                    else {
                        prev->next = p->left;
                        prev = prev->next;
                    }
                }
                if (p->right != NULL) {
                    if (head == NULL) {
                        head = p->right;
                        prev = head;
                    }
                    else {
                        prev->next = p->right;
                        prev = prev->next;
                    }
                }
                p = p->next;
            }
            if (prev != NULL) prev->next = NULL;
            last = head;
        }
    }
};

int main() {
    TreeLinkNode *root = new TreeLinkNode(7);
    root->left = new TreeLinkNode(-10);
    root->right = new TreeLinkNode(2);
    root->left->left = new TreeLinkNode(-4);
    root->left->right = new TreeLinkNode(3);
    root->right->left = new TreeLinkNode(-8);
    root->left->right->right = new TreeLinkNode(-1);
    root->right->left->left = new TreeLinkNode(11);
    Solution s;
    s.connect(root);
    return 0;
}
