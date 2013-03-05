#include<iostream>

using namespace std;

enum { MAX = 30050 };

int ancestor[MAX], up[MAX], all[MAX];

int find_set(int x) {
	int tmp;
	if (x != ancestor[x]) {
		tmp = ancestor[x];
		ancestor[x] = find_set(ancestor[x]);
		up[x] += up[tmp];
	}
	return ancestor[x];
}

void union_set(int x, int y) {
	x = find_set(x), y = find_set(y);
	if (x == y)
		return ;
	ancestor[y] = x;
	up[y] += all[x];
	all[x] += all[y];
}

int main() {
	int p, a, b;
	char op;
	scanf("%d", &p);
	for (int i = 0; i < MAX; i++) {
		ancestor[i] = i;
		all[i] = 1;
	}
	for (int i = 0; i < p; i++) {
		getchar();
		scanf("%c", &op);
		if (op == 'M') {
			scanf("%d%d", &a, &b);
			union_set(a, b);
		}
		else if (op == 'C') {
			scanf("%d", &a);
			cout << (all[find_set(a)] - up[a] - 1) << endl;
		}
		else
			cout << "input error.\n";
	}
	return 0;
}