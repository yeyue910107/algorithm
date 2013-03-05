#include<iostream>
#include<algorithm>
using namespace std;

enum { MAX = 20 };
int sum = 0, flag[MAX] = {0}, tr[MAX][MAX], res = 0;

void dfs(int n, int m) {
	if (m == n) {
		res = max(res, sum);
		return ;
	}
	int tmp[2] = { 0 };
	for (int i = 0; i < m; i++) {
		if (flag[i])
			tmp[0] += tr[m][i];
		else
			tmp[1] += tr[m][i];
	}
	for (int i = 0; i < 2; i++) {
		flag[m] = i;
		sum += tmp[i];
		dfs(n, m + 1);
		sum -= tmp[i];
	}
}

int main() {
	int n;

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> tr[i][j];
		}
	}
	dfs(n, 1);
	cout << res << endl;
}