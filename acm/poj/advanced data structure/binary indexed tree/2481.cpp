#include<iostream>
#include<algorithm>
using namespace std;

enum { MAX = 100005 };

typedef struct cow {
	int l, r, id;
}Cow;

Cow cows[MAX];
int c[MAX], res[MAX], n, imax;

/*int cmp(const void *a, const void *b) {
	if (((Cow *)(a))->r == ((Cow *)(b))->r)
		return ((Cow *)(a))->l > ((Cow *)(b))->l;
	return ((Cow *)(a))->r < ((Cow *)(b))->r;
}*/
bool cmp(Cow a, Cow b) {
	if(a.r == b.r)
		return a.l < b.l;
	return a.r > b.r;
}

int lowbit(int x) {
	return x & (-x);
}

void update(int i, int num) {
	while (i <= imax) {
		c[i] += num;
		i += lowbit(i);
	}
}

int sum(int i) {
	int ans = 0;
	while (i > 0) {
		ans += c[i];
		i -= lowbit(i);
	}
	return ans;
}

int main() {
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;
		memset(c, 0, sizeof(c));
		imax = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &cows[i].l, &cows[i].r);
			cows[i].id = i;
			cows[i].l++;
			cows[i].r++;
			imax = max(imax, cows[i].l);
		}

		//qsort(cows + 1, n, sizeof(Cow), cmp);
		sort(cows + 1, cows + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			if (i == 1)
				res[cows[i].id] = sum(cows[i].l);
			else {
				if (cows[i].r == cows[i - 1].r && cows[i].l == cows[i - 1].l)
					res[cows[i].id] = res[cows[i - 1].id];
				else
					res[cows[i].id] = sum(cows[i].l);
			}
			update(cows[i].l, 1);
		}
		for (int i = 1; i <= n; i++)
			printf("%d%c", res[i], (i == n) ? '\n' : ' ');
	}
}