#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 5002, INF = 65535 };

void reverse_str(int n, char *s, char *t) {
	int i, j;
	for (i = 0, j = n - 1; i <= n / 2; i++, j--) {
		t[i] = s[j];
		t[j] = s[i];
	}
	t[n] = '\0';
}

int lcs(int n, char *s, char *t) {
	if (n == 1)
		return 0;
	int i, j, dp[3][MAX] = {0};
	for (i = 0; i < n && s[0] != t[i]; i++)
		;
	for (; i < n; i++)
		dp[0][i] = 1;
	for (i = 0; i < n && s[i] != t[0]; i++)
		;
	for (; i < n; i++)
		dp[2][i] = 1;

	for (i = 1; i < n; i++) {
		dp[1][0] = dp[2][i];
		for (j = 1; j < n; j++)  {
			if (s[i] == t[j])
				dp[1][j] = dp[0][j - 1] + 1;
			else
				dp[1][j] = max(dp[1][j - 1], dp[0][j]);
		}
		for (j = 0; j < n; j++)
			dp[0][j] = dp[1][j];
	}
	return dp[1][n - 1];
}

int get_ans(int n, char *s) {
	char t[MAX];

	reverse_str(n, s, t);
	return lcs(n, s, t);
}

int main() {
	int n;
	char s[MAX];
	cin >> n >> s;
	cout << (n - get_ans(n, s)) << endl;
	return 0;
}