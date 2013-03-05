#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum {MAX = 100, INF = -65535};
struct P{
	int i, j, h;
};

int cmp(const void *a, const void *b) {
	if (((P*)a)->h > ((P*)b)->h)
		return 1;
	return -1;
}

int get_ans(int s[][MAX], P p[], int row, int col) {
	int i, j, k, ans = INF, dp[MAX][MAX];
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			dp[i][j] = 1;
	
	qsort(p, row * col, sizeof(p[0]), cmp);
	for (k = 0; k < row * col; k++) {
		i = p[k].i; j = p[k].j;
		if (i > 0 && s[i - 1][j] < s[i][j]) dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
		if (i < row - 1 && s[i + 1][j] < s[i][j]) dp[i][j] = max(dp[i][j], dp[i + 1][j] + 1);
		if (j > 0 && s[i][j - 1] < s[i][j]) dp[i][j] = max(dp[i][j], dp[i][j - 1] + 1);
		if (j < col - 1 && s[i][j + 1] < s[i][j]) dp[i][j] = max(dp[i][j], dp[i][j + 1] + 1);
		if (ans < dp[i][j])
			ans = dp[i][j];
	}
	return ans;
}
int main() {
	int row, col, s[MAX][MAX];
	P p[MAX*MAX];
	cin >> row >> col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> s[i][j];
			p[col * i + j].i = i;
			p[col * i + j].j = j;
			p[col * i + j].h = s[i][j];
		}
	}
	cout << get_ans(s, p, row, col) << endl;
	return 0;
}