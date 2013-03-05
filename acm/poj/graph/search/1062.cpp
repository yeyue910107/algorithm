#include<iostream>
#include<algorithm>
using namespace std;

enum { MAX = 102, INF = 100000000 };

typedef struct node{
	int price, level, sub;
	node() { }
	node(int price, int level, int sub) : price(price), level(level), sub(sub) { }
}Node;

Node nodes[MAX];
int graph[MAX][MAX], limit, num;

bool level_ok(int level, int min_level, int max_level) {
	return (level <= max_level && level >= min_level);
}

void dijstra() {
	bool flag[MAX];
	int dis[MAX], mini = -1, min_price = INF, k = 0, res = INF;

	for (int p = 0; p <= limit; p++) {
		for (int k = 0; k < num; k++)
			flag[k] = false;
		flag[0] = true;
		int min_level = nodes[0].level - limit + p, max_level = nodes[0].level + p;
		for (int i = 0; i < num; i++)
			dis[i] = (level_ok(nodes[i].level, min_level, max_level) ? graph[0][i] : INF);
		for (int k = 1; k < num; k++) {
			min_price = INF; mini = 0;
			for (int i = 0; i < num; i++) {
				if (!flag[i] && level_ok(nodes[i].level, min_level, max_level) && dis[i] < min_price) {
					min_price = dis[i];
					mini = i;
				}
			}
			flag[mini] = true;
			for (int j = 0; j < num; j++) {
				if (!flag[j] && level_ok(nodes[j].level, min_level, max_level) && graph[mini][j] != INF && dis[mini] + graph[mini][j] < dis[j])
					dis[j] = dis[mini] + graph[mini][j];
			}
		}
		for (int i = 0; i < num; i++) {
			res = min(res, dis[i] + nodes[i].price);
		}
	}
	printf("%d\n", res);
}

int main() {
	scanf("%d%d", &limit, &num);
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			if (j != i)
				graph[i][j] = INF;
	for (int i = 0; i < num; i++) {
		scanf("%d%d%d", &nodes[i].price, &nodes[i].level, &nodes[i].sub);
		for (int j = 0; j < nodes[i].sub; j++) {
			int sub_no, sub_price;
			scanf("%d%d", &sub_no, &sub_price);
			graph[i][sub_no - 1] = sub_price;
		}
	}

	dijstra();
	return 0;
}