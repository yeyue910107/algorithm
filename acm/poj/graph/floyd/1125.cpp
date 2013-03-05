#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 105, INF = 65535 };
int s[MAX][MAX], dist[MAX][MAX][MAX];

void floyd(const int n) {
	int i, j, k;

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			dist[i][j][0] = s[i][j];
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				dist[i][j][k] = dist[i][j][k - 1];
				dist[i][j][k] = min(dist[i][k][k - 1] + dist[k][j][k - 1], dist[i][j][k]);
			}
		}
	}
}

void get_ans(const int n) {
	int tmp1, tmp2, tmp3, tmp;
	tmp1 = INF;
	for (int i = 1; i <= n; i++) {
		tmp2 = 0;
		for (int j = 1; j <= n; j++) {
			if (i != j) {
				tmp3 = INF;
				for (int k = 1; k <= n; k++)
					tmp3 = min(tmp3, dist[i][j][k]);
				tmp2 = max(tmp2, tmp3);
			}
		}
		if (tmp2 < tmp1) {
			tmp1 = tmp2;
			tmp = i;
		}
	}
	if (tmp1 == INF)
		printf("disjoint\n");
	else
		printf("%d %d\n", tmp, tmp1);
}

void reset(const int n) {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j)
				s[i][j] = INF;
}

int main() {
	int n, m, p, q;

	while (1) {
		scanf("%d", &n);
		if (n == 0)
			break;
		reset(n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &m);
			for (int j = 1; j <= m; j++) {
				scanf("%d%d", &p, &q);
				s[i][p] = q;
			}
		}
		floyd(n);
		get_ans(n);
	}
	return 0;
}