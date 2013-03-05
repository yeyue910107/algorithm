#include <iostream>
#include <algorithm>
#define MAX 100
#define INF -65535

using namespace std;

int column_sum(int t[][MAX], int i, int m, int n) {
	if (m == 0 && i == 0)
		return t[n][0];
	if (m == 0)
		return t[n][i] - t[n][i - 1];
	if (i == 0)
		return t[n][0] - t[m - 1][0];
	return (t[n][i] - t[m - 1][i]) - (t[n][i - 1] - t[m - 1][i - 1]);
}

/*int row_sum(short s[][MAX], int t[][MAX], int N, int m, int n) {
	int i, max, tmp, col;
	for (i = 0, max = INF, tmp = 0; i < N; i++) {
		col = column_sum(t, i, m, n);
		if (tmp + col <= 0)
			tmp = 0;
		else
			tmp += col;
		if (max < tmp)
			max = tmp;
	}
	return max;
}*/

int row_sum(short s[][MAX], int t[][MAX], int N, int m, int n) {
	int i, all, all0, start, start0, tmp, ans = INF;
	all0 = start0 = column_sum(t, N - 1, m, n);
	
	for (i = N - 2; i >= 0; i--) {
		tmp = column_sum(t, i, m, n);
		start = max(tmp, tmp + start0);
		all = max(start, all0);
		if (ans < all)
			ans = all;
		start0 = start; all0 = all;
	}
	return ans;
}

int main() {
	int k, i, j, N, max, tmp, t[MAX][MAX];
	short s[MAX][MAX];
	cin >> N;
	
	for (k = 0; k < N * N; k++) {
		i = k / N;
		j = k % N;
		cin >> s[i][j];
		if (i == 0 && j == 0)
			t[i][j] = s[i][j];
		else if (i == 0)
			t[i][j] = t[i][j - 1] + s[i][j];
		else if (j == 0)
			t[i][j] = t[i - 1][j] + s[i][j];
		else
			t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + s[i][j];
	}
	for (i = 0, max = INF; i < N; i++) {
		for (j = i; j < N; j++) {
			tmp = row_sum(s, t, N, i, j);
			if (max < tmp)
				max = tmp;
		}
	}
	cout << max << endl;
}
