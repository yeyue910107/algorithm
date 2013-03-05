#include <iostream>
#include <algorithm>
#define MAX_LEN 100000
#define MAX_STONE 101
#define MAX_VALUE 65535
#define GAP 100
using namespace std;

int get_ans(int stones[], int l, int s, int t, int m) {
	int dp[MAX_LEN], i, j, mini, tmp = 0;
	bool bit[MAX_LEN] = {false};
	dp[0] = 0;
	for (i = 0; i < m; i++) {
		if (i > 0 && stones[i] - stones[i - 1] - tmp >= GAP) {
			tmp = stones[i] - stones[i - 1] - GAP;
			//l -= tmp;
			bit[stones[i - 1] + GAP] = true;
			stones[i] = stones[i - 1] + GAP;
		}
		else
			bit[stones[i]] = true;
	}
	l -= tmp;
	for (i = 1; i <= l + t; i++) {
		mini = MAX_VALUE;
		for (j = i - s; j >= 0 && j >= i - t; j--) {
			if (mini > dp[j])
				mini = dp[j];
		}
		if (mini != MAX_VALUE && bit[i])
			dp[i] = mini + 1;
		else
			dp[i] = mini;
	}
	for (i = l, mini = dp[l]; i <= l + t; i++)
		mini = min(mini, dp[i]);
	return mini;
}
int main() {
	int l, s, t, m, i, stones[MAX_STONE];
	cin >> l >> s >> t >> m;
	stones[0] = 0;
	for (i = 0; i < m; i++)
		cin >> stones[i];
	cout << get_ans(stones, l, s, t, m) << endl;
	return 0;
}
/*
1000
2 3 5
2 3 500 650 800
*/