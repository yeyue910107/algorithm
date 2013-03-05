#include<iostream>
#include<cmath>
using namespace std;

enum { MAX = 1024 };

int px[MAX], py[MAX], ancestor[MAX];
bool ok[MAX] = { false };

int find_set(int x) {
	if (x != ancestor[x]) {
		ancestor[x] = find_set(ancestor[x]);
	}
	return ancestor[x];
}

void union_set(int x, int y) {
	x = find_set(x); y = find_set(y);
	ancestor[y] = x;
}

double dis(const int a, const int b) {
	return sqrt((double)((px[a] - px[b])*(px[a] - px[b]) + (py[a] - py[b])*(py[a] - py[b])));
}

void update(const int a, const int n, const int d) {
	for (int i = 0; i < n; i++) {
		if (a != i && ok[i] && dis(a, i) <= d) {
			union_set(a, i);
		}
	}
}

bool test(const int a, const int b) {
	return (find_set(a) == find_set(b));
}

int main() {
	int n, d, a, b;
	char op;
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &px[i], &py[i]);
	for (int i = 0; i < MAX; i++)
		ancestor[i] = i;
	getchar();
	while (scanf("%c", &op) != EOF) {
		if (op == 'O') {
			scanf("%d", &a);
			ok[a - 1] = true;
			update(a - 1, n, d);
		}
		else if (op == 'S') {
			scanf("%d%d", &a, &b);
			printf(test(a - 1, b - 1) ? "SUCCESS\n" : "FAIL\n");
		}
		else
			cout << "input error.\n";
		getchar();
	}
	return 0;
}