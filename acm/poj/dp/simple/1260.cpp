#include<iostream>
#include<algorithm>
using namespace std;

enum { MAX = 1002, EXTRA = 10 };

int get_ans(int n, int a[], int p[], int sum[]) {
	int i, j, dp[MAX] = {0};
	dp[0] = (a[0] + EXTRA)*p[0];
	for (i = 1; i < n; i++) {
		dp[i] = (sum[i] + EXTRA)*p[i];
		for (j = 0; j < i; j++)
			dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j] + EXTRA)*p[i]);
	}
	return dp[n - 1];
}

int main() {
	int num, n, a[MAX], p[MAX], sum[MAX];
	cin >> num;
	while (num--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[i] >> p[i];
			sum[i] = (i == 0) ? a[i] : sum[i - 1] + a[i];
		}
		cout << get_ans(n, a, p, sum) << endl;
	}
	return 0;
}