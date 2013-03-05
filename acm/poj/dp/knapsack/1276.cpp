#include <iostream>
#include <algorithm>

using namespace std;

enum { MAX = 10001, STATE = 100001 };

int get_ans(int s[], int cash, int n) {
	int i, j;
	bool dp[STATE] = { false };
	dp[0] = true;
	for (i = 0; i < n; i++) {
		for (j = cash; j >= 0; j--) {
			if (j >= s[i] && dp[j - s[i]])
				dp[j] = true;
		}
	}
	while (cash-- && !dp[cash + 1])
		;
	return cash + 1;
}

int main() {
	int cash, N, s[MAX], n, d, k, p;
	while (scanf("%d %d", &cash, &N) != EOF) {
		k = 0;
		for (int i = 0; i < N; i++) {
			cin >> n >> d;
			p = 1;
			while (n - p >= 0) {
				s[k++] = d * p;
				n -= p;
				p *= 2;
			}
			if (n)
				s[k++] = d * n;
		}
		cout << get_ans(s, cash, k) << endl;
	}
	return 0;
}