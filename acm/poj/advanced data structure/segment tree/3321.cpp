#include<iostream>
using namespace std;

enum { MAX = 100010, SIZE = 100 };

typedef struct segtree {
	int l, r, sum;
	segtree() { }
	segtree(int l, int r) : l(l), r(r), sum(1) { }
	segtree(int l, int r, int sum) : l(l), r(r), sum(sum) { }
}SegTree;

int tree[MAX][SIZE];
int count, start[MAX], finish[MAX], num[MAX];
bool exist[MAX] = { false };
SegTree node[MAX*6];

void dfs(const int i) {
	start[i] = count++;
	for (int k = 0; k < num[i]; k++)
		dfs(tree[i][k]);
	finish[i] = count++;
}

int build_tree(const int l, const int r, const int i) {
	if (l == r) {
		node[i] = SegTree(l, r);
		return 1;
	}
	int mid = (l+r) / 2, left, right;
	left = build_tree(l, mid, (i<<1) + 1);
	right = build_tree(mid + 1, r, (i<<1) + 2);
	node[i] = SegTree(l, r, left + right);
	return left + right;
}

void change(const int l, const int r, const int m, const int i, bool exist) {
	if (exist) {
		node[i].sum++;
	}
	else
		node[i].sum--;
	if (l == r)
		return ;
	int mid = (l+r) / 2;
	if (m <= mid)
		change(l, mid, m, (i<<1) + 1, exist);
	else
		change(mid + 1, r, m, (i<<1) + 2, exist);
}

int query(const int l, const int r, const int i, const int s, const int f) {
	if (s == l && f == r)
		return node[i].sum;
	int mid = (l+r) / 2;
	if (f <= mid)
		return query(l, mid, (i<<1) + 1, s, f);
	if (s > mid)
		return query(mid + 1, r, (i<<1) + 2, s, f);
	return query(l, mid, (i<<1) + 1, s, mid) + query(mid + 1, r, (i<<1) + 2, mid + 1, f);
}

int main() {
	int n, m, a, b;
	char op[3];
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d", &a, &b);
		tree[a - 1][num[a - 1]++] = b - 1;
	}
	dfs(0);
	build_tree(0, (n<<1) - 1, 0);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		if (*op == 'Q') {
			scanf("%d", &b);
			printf("%d\n", query(0, (n<<1) - 1, 0, start[b - 1], finish[b - 1]) / 2);
		}
		else if (*op == 'C') {
			scanf("%d", &b);
			change(0, (n<<1) - 1, start[b - 1], 0, exist[b - 1]);
			change(0, (n<<1) - 1, finish[b - 1], 0, exist[b - 1]);
			exist[b - 1] = !exist[b - 1];
		}
	}
	return 0;
}