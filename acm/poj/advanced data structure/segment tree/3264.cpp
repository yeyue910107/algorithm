/*#include<iostream>
#include<algorithm>
using namespace std;

enum { MAXN = 50002, MAXQ = 200005 };

typedef struct segtree {
	int l, r, max, min;
	segtree() { }
	segtree(int l, int r) : l(l), r(r) { }
	segtree(int l, int r, int max, int min) : l(l), r(r), max(max), min(min) { }
}SegTree;

typedef struct value {
	int max, min;
	value() { }
	value(int max, int min) : max(max), min(min) { }
}Value;

SegTree node[3*MAXN];

int build_tree(int h[], const int l, const int r, const int i) {
	if (l == r) {
		node[i] = SegTree(l, r, h[l], h[l]);
		return i;
	}
	int mid = (l+r) / 2, left, right;
	left = build_tree(h, l, mid, 2*i + 1);
	right = build_tree(h, mid + 1, r, 2*i + 2);
	node[i] = SegTree(l, r, max(node[left].max, node[right].max), min(node[left].min, node[right].min));
	return i;
}

Value dif(const int a, const int b, const int l, const int r, const int i) {
	if (a == l && b == r)
		return Value(node[i].max, node[i].min);
	int mid = (l+r) / 2;
	if (b <= mid)
		return dif(a, b, l, mid, 2*i + 1);
	if (a > mid)
		return dif(a, b, mid + 1, r, 2*i + 2);
	Value left = dif(a, mid, l, mid, 2*i + 1), right = dif(mid + 1, b, mid + 1, r, 2*i + 2);
	return Value(max(left.max, right.max), min(left.min, right.min));

}

int main() {
	int n, q, h[MAXN], a, b;
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++)
		scanf("%d", &h[i]);
	build_tree(h, 0, n - 1, 0);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &a, &b);
		Value res = dif(a - 1, b - 1, 0, n - 1, 0);
		printf("%d\n", res.max - res.min);
	}
	return 0;
}*/

#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

enum { MAXN = 50002, MAX = 20 };

typedef struct value {
	int max, min;
	value() { }
	value(int max, int min) : max(max), min(min) { }
}Value;

Value dp[MAXN][MAX];

void init(int h[], const int n) {
	int i, j;
	for (i = 1; i <= n; i++)
		dp[i][0] = Value(h[i], h[i]);
	for (j = 1; j <= log(double(n+1)) / log(2.0); j++)
		for (i = 1; i <= n + 1 - (1<<j); i++)
			dp[i][j] = Value(max(dp[i][j - 1].max, dp[i + (1<<(j-1))][j - 1].max), min(dp[i][j - 1].min, dp[i + (1<<(j-1))][j - 1].min));
}

Value query(const int l, const int r) {
	int k = log(double(r - l + 1)) / log(2.0);
	return Value(max(dp[l][k].max, dp[r - (1<<k) + 1][k].max), min(dp[l][k].min, dp[r - (1<<k) + 1][k].min));
}


int main() {
	int n, q, h[MAXN], a, b;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &h[i]);
	init(h, n);
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &a, &b);
		Value res = query(a, b);
		printf("%d\n", res.max - res.min);
	}
	return 0;
}