#include <iostream>
#include <algorithm>

using namespace std;
enum { MAX = 20, STATE = 16000, DELTA = 8000 };

int get_ans(int d[], int w[], int n, int m) {
	int i, j, k, dp[MAX][STATE] = {0};

	for (k = 0; k < n; k++) {
		dp[0][w[0] * d[k] + DELTA] = 1;
	}

	for (i = 1; i < m; i++) {
		for (j = 0; j < STATE; j++) {
			for (k = 0; k < n; k++) {
				if (j - w[i]*d[k] >= 0 && dp[i - 1][j - w[i]*d[k]])
					dp[i][j] += dp[i - 1][j - w[i]*d[k]];
			}
		}
	}
	return dp[m - 1][DELTA];
}

int main() {
	int n, m, d[MAX], w[MAX];

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> d[i];
	for (int i = 0; i < m; i++)
		cin >> w[i];
	cout << get_ans(d, w, n, m) << endl;
	return 0;
}