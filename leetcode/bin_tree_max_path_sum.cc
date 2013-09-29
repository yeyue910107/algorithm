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
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (root == NULL)
        	return 0;
        int res = NEG_INF;
        getRes(root, res);
        return res;
    }
private:
	const int NEG_INF = -65535;
	int getRes(TreeNode *node, int &res) {
		if (node == NULL)
			return NEG_INF;
		int left_max = getRes(node->left, res), right_max = getRes(node->right, res);
		int child_max = max(left_max, right_max), child_min = min(left_max, right_max);
		res = max(res, max(child_max+child_min+node->val, max(child_max+node->val, max(child_max, node->val))));
		return (child_max > 0) ? (child_max+node->val) : node->val;
	}
};
