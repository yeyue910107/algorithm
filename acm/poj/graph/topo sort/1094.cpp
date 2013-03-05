#include<iostream>

using namespace std;

enum { MAX = 26 };

int topo_sort(int n, int m, bool graph[][MAX], int degree[]) {
	int i, j, num = 0, tmp = 0, d[MAX];
	char res[MAX];
	bool flag = false, g[MAX][MAX];
	for (i = 0; i < n; i++) {
		d[i] = degree[i];
		for (j = 0; j < n; j++)
			g[i][j] = graph[i][j];
	}
	for (i = 0; i < n; i++) {
		for (j = 0, num = 0; j < n; j++) {
			if (d[j] == 0) {
				num++;
				tmp = j;
			}
		}
		if (num == 0) {
			cout << "Inconsistency found after " << m << " relations.\n";
			return 2;
		}
		d[tmp] = -1;
		if (num == 1)
			res[i] = (char)(tmp + 'A');
		else
			flag = true;
		for (j = 0; j < n; j++) {
			if (g[tmp][j]) {
				g[tmp][j] = false;
				d[j]--;
			}
		}
	}
	if (flag)
		return 1;
	else {
		res[i] = '\0';
		cout << "Sorted sequence determined after " << m << " relations: " << res << ".\n";
		return 0;
	}
		
}

int main() {
	int n, m, ret;
	char c1, c2;
	bool flag;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;
		bool graph[MAX][MAX] = { false };
		int degree[MAX] = { 0 };
		flag = false;
		getchar();
		for (int i = 0; i < m; i++) {
			c1 = getchar(); getchar(); c2 = getchar(); getchar();
			if (!flag) {
				if (!graph[c1 - 'A'][c2 - 'A']) {
					graph[c1 - 'A'][c2 - 'A'] = true;
					degree[c2 - 'A']++;
				}
				ret = topo_sort(n, i + 1, graph, degree);
				if (ret == 0 || ret == 2) {
					flag = true;
				}
			}
		}
		if (ret == 1)
			cout << "Sorted sequence cannot be determined.\n";
	}
	return 0;
}