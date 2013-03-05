#include <iostream>
#include <queue>
#define MAX_M 10
#define MAX_N 10
#define MAX_VALUE 65535
using namespace std;
struct E{
	int num, i, j;
	E() {}
	E(int num, int i, int j) : num(num), i(i), j(j) {}
};
int get_ans(int matrix[][MAX_N], int m, int n) {
	queue<E> q;
	int min = MAX_VALUE;
	q.push(E(matrix[0][0], 0, 0));
	while (!q.empty()) {
		E e = q.front();
		q.pop();
		if (e.i == m - 1 && e.j == n - 1) {
			if (e.num > 0 && e.num < min)
				min = e.num;
			continue;
		}
		if (e.i < m - 1)
			q.push(E(matrix[e.i + 1][e.j] + e.num, e.i + 1, e.j));
		if (e.j < n - 1)
			q.push(E(matrix[e.i][e.j + 1] + e.num, e.i, e.j + 1));
	}
	return (min == MAX_VALUE) ? -1 : min;
}
int main() {
	int m, n, i, j, matrix[MAX_M][MAX_N];
	while (cin >> m >> n) {
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				cin >> matrix[i][j];
		cout << get_ans(matrix, m, n) << endl;
	}
}