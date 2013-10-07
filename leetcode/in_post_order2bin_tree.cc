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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        int k = inorder.size()-1;
        return build(inorder, postorder, 0, k, k);
    }

private:
    TreeNode *build(vector<int> &in, vector<int> &post, const int i, const int j, int &k) {
        if (k < 0 || k >= post.size() || i > j)
            return NULL;
		int index= _find(in, post[k]);
        if (index == -1)
            return NULL;
        TreeNode* node = new TreeNode(post[k]);
		k--;
        node->right = build(in, post, index + 1, j, k);
        node->left = build(in, post, i, index - 1, k);
        return node;
    }

	int _find(vector<int> v, const int num) {
		int size = v.size();
		for (int i = 0; i < size; i++)
			if (v[i] == num)
				return i;
		return -1;
	}
};
