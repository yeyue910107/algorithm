/*
Input

Each test case contains three parts.
The first part is two numbers N K, whose meanings we have talked about just now. We denote the nodes by 1 2 бн N. Since it is a tree, each node can reach any other in only one route. (1<=N<=100, 0<=K<=200)
The second part contains N integers (All integers are nonnegative and not bigger than 1000). The ith number is the amount of apples in Node i. 
The third part contains N-1 line. There are two numbers A,B in each line, meaning that Node A and Node B are adjacent.

Note: Wshxzt starts at Node 1.
Output

For each test case, output the maximal numbers of apples Wshxzt can eat at a line.

Sample Input

2 1 
0 11
1 2
3 2
0 1 2
1 2
1 3
5 3
1 5 2 1 1
1 2
1 3
3 4
4 5
Sample Output

11
2
*/
#include<stdio.h>
enum {MAX_NODE = 100, MAX_K = 201};

typedef struct{
	int index, apple_num, neibough_num, apple_num_bak;
	int neiboughs[MAX_NODE];
	int apples[MAX_K];
}NODE;

int get_apples(int n, int i, int j, NODE nodes[]) {
	int tmp, p;
	
	if (nodes[i].apples[j] != -1) {
		nodes[i].apple_num = 0;
		return nodes[i].apples[j];
	}
	if (i == 0 && j == 0) {
		nodes[i].apple_num = 0;
		return nodes[i].apples[j];
	}
	if (j == 0) {
		nodes[i].apples[j] = -1;
		return nodes[i].apples[j];
	}
		
	for (p = 0; p < nodes[i].neibough_num; p++) {
		nodes[i].apple_num = nodes[i].apple_num_bak;
		nodes[nodes[i].neiboughs[p]].apple_num = nodes[nodes[i].neiboughs[p]].apple_num_bak;
		tmp = get_apples(n, nodes[i].neiboughs[p], j - 1, nodes);
		if (tmp == -1)
			continue;
		tmp += nodes[i].apple_num;
		nodes[i].apple_num = 0;
		if (nodes[i].apples[j] < tmp)
			nodes[i].apples[j] = tmp;
	}
	return nodes[i].apples[j];
}

int main() {
	int i, j, n, k, tmp1, tmp2, res, tmp;
	NODE nodes[MAX_NODE];
	while(scanf("%d%d", &n, &k) != EOF) {
		for (i = 0; i < n; i++) {
			scanf("%d", &(nodes[i].apple_num_bak));
			nodes[i].index = i;
			nodes[i].neibough_num = 0;
		}
		for (i = 0, j = 0; i < n - 1; i++) {
			scanf("%d%d", &tmp1, &tmp2);
			nodes[tmp1 - 1].neiboughs[nodes[tmp1 - 1].neibough_num++] = tmp2 - 1;
			nodes[tmp2 - 1].neiboughs[nodes[tmp2 - 1].neibough_num++] = tmp1 - 1;
		}

		for (i = 0; i < n; i++) 
			for (j = 0; j <= k; j++)
				nodes[i].apples[j] = -1;

		nodes[0].apples[0] = nodes[0].apple_num_bak;

		for (i = 0, res = 0; i < n; i++) {
			tmp = get_apples(n, i, k, nodes);
			if (res < tmp)
				res = tmp;
		}
		printf("%d\n", res);
	}
	return 0;
}
