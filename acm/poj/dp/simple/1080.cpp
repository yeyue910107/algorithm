#include <iostream>
#include <algorithm>
using namespace std;
enum { MAX = 208, INF = 65535};

const int TABLE[5][5] = {5, -1, -2, -1, -3, 
						 -1, 5, -3, -2, -4, 
						 -2, -3, 5, -2, -2, 
						 -1, -2, -2, 5, -1, 
						 -3, -4, -2, -1, -INF};
int DP[MAX][MAX];

void initDP(const int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			DP[i][j] = INF;
	DP[0][0] = 0;
}

const int value(const char c) {
	switch (c) {
		case 'A':
			return 0;
		case 'C':
			return 1;
		case 'G':
			return 2;
		case 'T':
			return 3;
		case '-':
			return 4;
		default:
			return -1;
	}
}

const int get_ans(const char *s, const char *t, const int m, const int n) {
	if (DP[m][n] != INF)
		return DP[m][n];
	if (n == 0) {
		DP[m][n] = get_ans(s, t, m - 1, n) + TABLE[value(s[m - 1])][value('-')];
		return DP[m][n];
	}
	if (m == 0) {
		DP[m][n] = get_ans(s, t, m, n - 1) + TABLE[value('-')][value(t[n - 1])];
		return DP[m][n];
	}
	int tmp1 = get_ans(s, t, m - 1, n - 1) + TABLE[value(s[m - 1])][value(t[n - 1])],
		tmp2 = get_ans(s, t, m - 1, n) + TABLE[value(s[m - 1])][value('-')],
		tmp3 = get_ans(s, t, m, n - 1) + TABLE[value('-')][value(t[n - 1])];
	DP[m][n] = max(max(tmp1, tmp2), tmp3);
	return DP[m][n];
}

int main() {
	int num, slen, tlen;
	char s[MAX], t[MAX];
	
	cin >> num;
	while (num-- > 0) {
		cin >> slen >> s >> tlen >> t;
		initDP(slen + tlen);
		cout << get_ans(s, t, slen, tlen) << endl;
	}
	return 0;
}