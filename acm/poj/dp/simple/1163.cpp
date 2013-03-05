#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum {MAX = 100};
int dp[MAX][MAX];

int get_ans(vector<int> t[MAX], int row) {
	int ans = t[0][0], i, j;
	for (i = 1; i < row; i++) {
		for (j = 0; j < i + 1; j++) {
			if (j == 0)
				dp[i][j] = t[i][j] + dp[i - 1][j];
			else if (j == i)
				dp[i][j] = t[i][j] + dp[i - 1][j - 1];
			else
				dp[i][j] = max(t[i][j] + dp[i - 1][j - 1], t[i][j] + dp[i - 1][j]);
			if (i == row - 1)
				ans = max(ans, dp[i][j]);
		}
	}
	return ans;
}
int main() {
	int row, tmp;
	vector<int> t[MAX];
	cin >> row;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < i + 1; j++) {
			cin >> tmp;
			t[i].push_back(tmp);
			dp[i][j] = tmp;
		}
	}
	cout << get_ans(t, row) << endl;
	return 0;
}