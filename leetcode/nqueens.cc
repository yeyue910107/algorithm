#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    static const int MAX = 10;
    int queen[MAX];
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string>> res;
        if (n == 0) return res;
        memset(queen, -1, sizeof(queen));
        doQueens(0, n, res);
        return res;
    }
private:
    void doQueens(int k, const int n, vector<vector<string>> &res) {
        if (k == n) {
            addRes(res, n);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (judge(k, i, n)) {
                queen[k] = i;
                doQueens(k+1, n, res);
                queen[k] = i;
            }
        }
    }
    bool judge(const int i, const int k, const int n) {
        for (int j = 0; j < i; j++) {
	    if (queen[j] == k || queen[j] - k == i - j || queen[j] - k == j - i)
		return false;
        }
        return true;
    }
    void addRes(vector<vector<string>> &res, const int n) {
        vector<string> tmp;
        for (int i = 0; i < n; i++) {
            string row = "";
            for (int j = 0; j < n; j++) {
                row += ((j == queen[i]) ? 'Q' : '.');
            }
            tmp.push_back(row);
        }
        res.push_back(tmp);
    }
};

int main() {
	Solution s;
	vector<vector<string>> res;
	res = s.solveNQueens(4);
	return 0;
}
