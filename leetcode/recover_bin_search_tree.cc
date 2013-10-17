#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode *prev, *last;
    bool flag;
    void recoverTree(TreeNode *root) {
        prev = last = NULL;
        flag = false;
        inorder(root);
        if (last != NULL)
            swap(last, prev);
    }
private:
    void inorder(TreeNode *root) {
        if (root == NULL || flag) return ;
        if (root->left != NULL)
            inorder(root->left);
        if (last != NULL && last->val < root->val) {
            swap(last, prev);
            flag = true;
            last = NULL;
            return ;
        }
        if (prev == NULL || (last == NULL && root->val < prev->val))
            last = prev;
        prev = root;
        
        if (root->right != NULL)
            inorder(root->right);
    }
    
    void swap(TreeNode *node1, TreeNode *node2) {
        int tmp = node1->val;
        node1->val = node2->val;
        node2->val = tmp;
    }
};

int main() {
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(3);
    root->right = new TreeNode(1);
    Solution s;
    s.recoverTree(root);
    return 0;
}
