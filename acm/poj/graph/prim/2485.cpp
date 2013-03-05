#include<iostream>
#include<algorithm>

using namespace std;
enum { MAX = 500, INF = 65536 };

int highway[MAX][MAX], n;

void prim() {
	int i, j, k, min_cost, min_index, lowcost[MAX], res;
	bool flag[MAX] = { false };
	for (i = 0; i < n; i++)
		lowcost[i] = highway[0][i];
	flag[0] = true;
	res = 0;
	for (i = 0; i < n - 1; i++) {
		min_cost = INF;
		for (j = 0; j < n; j++) {
			if (!flag[j] && lowcost[j] < min_cost) {
				min_cost = lowcost[j];
				min_index = j;
			}
		}
		res = max(min_cost, res);
		if (i == n - 2)
			break;
		flag[min_index] = true;
		lowcost[min_index] = 0;
		for (j = 0; j < n; j++) {
			if (!flag[j] && highway[min_index][j] < lowcost[j])
				lowcost[j] = highway[min_index][j];
		}
	}
	printf("%d\n", res);
} 

int main() {
	int num;
	scanf("%d", &num);
	while (num-- > 0) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &highway[i][j]);
		prim();
	}
}