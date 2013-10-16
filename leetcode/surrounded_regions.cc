#include <iostream>
#include <vector>

using namespace std;

static const int DX[4] = {0, 1, 0, -1}, DY[4] = {1, 0, -1, 0}, MAX = 100;
class Solution {
public:
    bool flag[MAX][MAX];
    int m, n;
    void solve(vector<vector<char>> &board) {
        m = board.size();
        if (m == 0) return ;
        n = board[0].size();
        if (n == 0) return ;
        memset(flag, false, sizeof(flag));
        for (int i = 0; i < n; i++) {
            if (!flag[0][i] && board[0][i] == 'O')
                dfs(board, 0, i);
            if (!flag[m - 1][i] && board[m - 1][i] == 'O')
                dfs(board, m - 1, i);
        }
        for (int i = 1; i < m - 1; i++) {
            if (!flag[i][0] && board[i][0] == 'O')
                dfs(board, i, 0);
            if (!flag[i][n - 1] && board[i][n - 1] == 'O')
                dfs(board, i, n - 1);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!flag[i][j] && board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
private:
    void dfs(vector<vector<char>> &board, const int i, const int j) {
        flag[i][j] = true;
        for (int k = 0; k < 4; k++) {
            int xx = i + DX[k], yy = j + DY[k];
            if (xx < 0 || xx == m || yy < 0 || yy == n)
                continue;
            if (!flag[xx][yy] && board[xx][yy] == 'O') {
                dfs(board, xx, yy);
            }
        }
    }
};

int main() {
    int a[6][6] = {'O', 'O', 'O', 'O', 'X', 'X',
                   'O', 'O', 'O', 'X', 'O', 'X',
                   'O', 'X', 'X', 'X', 'O', 'X',
                   'O', 'X', 'O', 'O', 'X', 'O',
                   'O', 'X', 'X', 'X', 'O', 'O',
                   'O', 'X', 'O', 'O', 'O', 'O' };
    vector<vector<char>> board;
    for (int i = 0; i < 6; i++) {
        vector<char> v;
        for (int j = 0; j < 6; j++) {
            v.push_back(a[i][j]);
        }
        board.push_back(v);
    }
    Solution s;
    s.solve(board);
    return 0;
}
