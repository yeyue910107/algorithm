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
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> res;
        vector<int> cur;
        findPath(root, sum, cur, res);
        return res;
    }
    
private:
    void findPath(TreeNode *node, int sum, vector<int> &cur, vector<vector<int>> &res) {
        if (node == NULL)
            return;
        if (node->left == NULL && node->right == NULL) {
            if (node->val == sum) {
                vector<int> tmp(cur);
                tmp.push_back(node->val);
                res.push_back(tmp);
            }
            return;
        }
        cur.push_back(node->val);
        findPath(node->left, sum - node->val, cur, res);
        findPath(node->right, sum - node->val, cur, res);
        cur.pop_back();
    }
};

int main() {
	TreeNode *root = new TreeNode(1);
	Solution s;
	vector<vector<int>> res = s.pathSum(root, 1);
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[i].size(); j++)
			cout << res[i][j] << endl;
	}
	return 0;
}
