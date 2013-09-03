/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL)
            return true;
        return (getDepth(root) != -1);
    }
private:
    int getDepth(TreeNode* node) {
        if (node == NULL)
            return 0;
        int l = getDepth(node->left), r = getDepth(node->right);
        if (l == -1 || r == -1 || abs(l-r) > 1)
            return -1;
        
        return max(l, r)+1;
    }
};