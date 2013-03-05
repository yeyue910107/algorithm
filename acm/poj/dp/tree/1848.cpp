#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NUM 100
using namespace std;

struct Node {
	int child_num;
	vector<int> childs;
	Node() : child_num(0){ }
	Node(int child_num) { 
		childs.resize(child_num);
	}
};

int get_ans(vector<Node> nodes, int i, int p) {
	int j, k, tmp, ans;
	if (nodes[i].child_num == 0) {
		return (p > 0);
	}
	if (p == 1) {
		for (j = 0, tmp = 0; j < nodes[i].child_num; j++)
			tmp += get_ans(nodes, nodes[i].childs[j], 0);
		return tmp + 1;
	}
	if (nodes[i].child_num == 2 && nodes[nodes[i].childs[0]].child_num == 0 && nodes[nodes[i].childs[1]].child_num == 0)
			return 1;
	for (j = 0, tmp = 0, ans = MAX_NUM; j < nodes[i].child_num; j++) {
		tmp = get_ans(nodes, nodes[i].childs[j], 1);
		for (k = 0; k < nodes[i].child_num; k++) {
			if (nodes[i].childs[k] != nodes[i].childs[j])
				tmp += get_ans(nodes, nodes[i].childs[k], 0);
		}
		if (ans > tmp)
			ans = tmp;
	}
	return ans;
}

int main() {
	int i, num, node1, node2;
	vector<Node> nodes;
	cin >> num;
	nodes.resize(num);
	for (i = 1; i < num; i++) {
		cin >> node1 >> node2;
		nodes[node1 - 1].childs.push_back(node2 - 1);
		nodes[node1 - 1].child_num++;
	}
	cout << get_ans(nodes, 0, 0) << endl;
	return 0;
}