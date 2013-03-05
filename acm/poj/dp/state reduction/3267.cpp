#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

enum { INF = 65535, MAX = 602, LEN = 302};

int remove(char *word, int end, char *dic[], int dp[], int n) {
	int i, j, k, len, tmp, res = INF;
	for (i = 0; i < n; i++) {
		len = strlen(dic[i]);
		for (tmp = 0, j = end, k = len - 1; j >= 0 && k >= 0; j--) {
			if (dic[i][k] != word[j])
				tmp++;
			else
				k--;
		}
		if (k == -1) {
			res = ((j == -1) ? min(res, tmp) : min(res, dp[j] + tmp));
		}
	}
	return res;
}

int get_ans(int n, int m, char *word, char *dic[]) {
	int i, dp[LEN] = {0};
	dp[0] = min(1, remove(word, 0, dic, dp, n));
	for (i = 1; i < m; i++)
		dp[i] = min(dp[i - 1] + 1, remove(word, i, dic, dp, n));
	return dp[m - 1];
}

int main() {
	int n, m;
	char word[LEN], *dic[MAX];
	cin >> n >> m >> word;
	for (int i = 0; i < n; i++) {
		dic[i] = (char *)malloc(LEN);
		cin >> dic[i];
	}
	cout << get_ans(n, m, word, dic) << endl;
	return 0;
}