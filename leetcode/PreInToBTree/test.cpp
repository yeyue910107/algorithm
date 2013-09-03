#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		int k = 0;
        return build(preorder, inorder, 0, preorder.size() - 1, k);
    }
private:
    TreeNode *build(vector<int> &pre, vector<int> &in, const int i, const int j, int &k) {
        if (k < 0 || k >= pre.size() || i > j)
            return NULL;
		int index= _find(in, pre[k]);
        if (index == -1)
            return NULL;
        TreeNode* node = new TreeNode(pre[k]);
		k++;
        node->left = build(pre, in, i, index - 1, k);
        node->right = build(pre, in, index + 1, j, k);
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

int main() {
	int test1[3] = {1, 2, 3}, test2[3] = {2, 1, 3};
	vector<int> pre(test1, test1+3);
	vector<int> in(test2, test2+3);
	Solution s;
	TreeNode *t = s.buildTree(pre, in);
	return 0;
}