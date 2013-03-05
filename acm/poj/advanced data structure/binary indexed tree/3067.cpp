#include<iostream>
#include<algorithm>

using namespace std;
enum { MAX = 1010};
typedef struct highway {
	int w, e;
}Highway;

int n, m, k, imax;
long long c[MAX];
Highway hw[MAX * MAX];

int lowbit(int x) {
	return x & (-x);
}

void update(int i, int num) {
	while (i <= imax) {
		c[i] += num;
		i += lowbit(i);
	}
}

long long sum(int i) {
	long long res = 0;
	while (i > 0) {
		res += c[i];
		i -= lowbit(i);
	}
	return res;
}

bool cmp(Highway a, Highway b) {
	if (a.e == b.e)
		return a.w > b.w;
	return a.e > b.e;
}

int main() {
	int num;
	long long total;
	scanf("%d", &num);
	for (int j = 1; j <= num; j++) {
		scanf("%d%d%d", &n, &m, &k);
		memset(c, 0, sizeof(c));
		imax = 0;
		for (int i = 1; i <= k; i++) {
			scanf("%d%d", &hw[i].e, &hw[i].w);
			imax = max(hw[i].w, imax);
		}
		sort(hw + 1, hw + k + 1, cmp);
		
		total = 0;
		update(hw[1].w, 1);
		for (int i = 2; i <= k; i++) {
			total += sum(hw[i].w - 1);
			update(hw[i].w, 1);
		}
		printf("Test case %d: %lld\n", j, total);
	}
	return 0;
}
