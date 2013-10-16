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
    int maxPathSum(TreeNode *root) {
        if (root == NULL)
            return 0;
        int res = INT_MIN;
        getRes(root, res);
        return res;
    }
private:
    int getRes(TreeNode *node, int &res) {
        if (node == NULL)
            return INT_MIN;
        int left_max = getRes(node->left, res), right_max = getRes(node->right, res);
        int child_max = max(left_max, right_max), child_min = min(left_max, right_max);
        res = max(res, max(child_max+child_min+node->val, max(child_max+node->val, max(child_max, node->val))));
        return (child_max > 0) ? (child_max+node->val) : node->val;
    }
};
