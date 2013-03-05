#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 1024, INF = 65535 };

int get_ans(int n, int s[]) {
	int i, j, tmp, res = 1, dp[MAX] = {0};
	dp[0] = 1;
	for (i = 1; i < n; i++) {
		for (tmp = 1, j = 0; j < i; j++) {
			if (s[j] < s[i])
				tmp = max(tmp, dp[j] + 1);
		}
		dp[i] = tmp;
		res = max(res, tmp);
	}
	return res;
}

int main() {
	int n, s[MAX];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	cout << get_ans(n, s) << endl;
	return 0;
}