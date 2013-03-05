#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define MAX 11
#define STATE (1<<MAX)
#define INF 65535
using namespace std;
long long dp[MAX + 2][STATE];
vector<int> state[STATE];

void dfs(int col, int s1, int s2, int n) {
	if (col >= n ) {
		if (s1 < (1<<n) && s2 < (1<<n))
			state[s2].push_back(s1);
		return;
	}
	dfs(col + 1, (s1 << 1)|1, s2 << 1, n);
	dfs(col + 1, s1 << 1, (s2 << 1)|1, n);
	dfs(col + 2, (s1 << 2)|3, (s2 << 2)|3, n);
}

long long get_ans(int m, int n) {
	int i, j, k, size, s;
	if (m < n)
		swap(m, n);
	dfs(0, 0, 0, n);
	dp[0][0] = 1;
	s = 1 << n;
	for (i = 1; i < m + 2; i++) {
		for (j = 0; j < s; j++) {
			size = state[j].size();
			for (k = 0; k < size; k++) {
				dp[i][j] += dp[i - 1][state[j][k]];
			}
		}
	}
	return dp[m + 1][s - 1];
}

int main() {
	int m, n, i;
	while (1) {
		cin >> m >> n;
		if (m == 0 && n == 0)
			break;
		if (m % 2 == 1 && n % 2 == 1)
			cout << 0 << endl;
		else {
			for (i = 0; i < STATE; i++)
				state[i].clear();
			memset(dp, 0, sizeof(dp));
			cout << get_ans(m, n) << endl;
		}
	}
	return 0;
}