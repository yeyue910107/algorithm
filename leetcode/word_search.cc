#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int MAX = 128;
const int X[4] = {0, 1, 0, -1};
const int Y[4] = {1, 0, -1, 0};//e s w n
bool visit[MAX][MAX];
class Solution {

public:
    bool exist(vector<vector<char> > &board, string word) {
        if (word.size() == 0)
            return true;
        int m = board.size(), n = board[0].size();
		memset(visit, 0, sizeof(visit));
        bool flag = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    flag |= _exist(board, word, i, j, 0, m, n);
                    if (flag) return true;
                }
            }
        }
        return false;
    }
private:
    bool _exist(vector<vector<char> > &board, string word, const int i, const int j, const int p, const int m, const int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || visit[i][j])
            return false;
        if (board[i][j] == word[p]) {
			if (p == word.size() - 1)
                return true;
			visit[i][j] = true;
            bool flag = false;
            for (int k = 0; k < 4; k++) {
                flag |= _exist(board, word, i+X[k], j+Y[k], p+1, m, n);
                if (flag) return true;
            }
        }
		visit[i][j] = false;
        return false;
    }
};

int main() {
	char s[5] = "aaaa";
	vector<char> row;
	vector<vector<char>> board;
	for (int i = 0; i < 4; i++)
		row.push_back(s[i]);
	board.push_back(row);
	board.push_back(row);
	board.push_back(row);
	string word = "aaaaaaaaaaaa";
	Solution so;
	bool res = so.exist(board, word);
	return 0;
}
