#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    void flatten(TreeNode *root) {
        stack<TreeNode *> st;
        TreeNode *p = root, *q = root;
        if (root != NULL) {
            do {
                while (p != NULL) {
                    if (p != root) {
                        q->left = p;
                        q = p;
                    }
                    st.push(p);
                    p = p->left;
                }
                p = st.top();
                st.pop();
                p = p->right;
            }
            while (!st.empty() || p != NULL);
            TreeNode *prev = root;
            p = root; q = root;
            while (q != NULL) {
                p->right = q->left;
                p = p->right;
                q = q->left;
                prev->left = NULL;
                prev = q;
            }
        }
    }
};

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    Solution s;
    s.flatten(root);
    return 0;
}
