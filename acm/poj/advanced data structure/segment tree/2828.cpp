#include<iostream>
using namespace std;

enum { MAX = 200002 };

typedef struct segtree {
	int l, r, free;
	segtree() { }
	segtree(int l, int r) : l(l), r(r), free(r - l + 1) { }
}SegTree;

SegTree node[3*MAX];

void build_tree(const int i, const int l, const int r, const int n) {
	node[i] = SegTree(l, r);
	if (l < r) {
		int mid = (l+r) / 2;
		build_tree(2*i + 1, l, mid, n);
		build_tree(2*i + 2, mid + 1, r, n);
	}
}

int update(const int i, int pos) {
	node[i].free--;
	if (node[i].l == node[i].r)
		return node[i].l;
	if (node[2*i + 1].free >= pos)
		return update(2*i + 1, pos);
	else {
		pos -= node[2*i + 1].free;
		return update(2*i + 2, pos);
	}
}

int main() {
	int n, res[MAX], pos[MAX], value[MAX];
	while ((scanf("%d", &n)) != EOF) {
		build_tree(0, 0, n - 1, n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &pos[i], &value[i]);
		}
		for (int i = n - 1; i >= 0; i--)
			res[update(0, pos[i] + 1)] = value[i];
		for (int i = 0; i < n; i++)
			printf("%d%c", res[i], (i == n - 1) ? '\n' : ' ');
	}
	return 0;
}