#include<iostream>
#include<queue>
#include<cstdlib>

using namespace std;

enum { MAX = 200 };

bool flag[MAX] = { false };

typedef struct node {
	int value, rem;
	struct node *pre;
	node() { }
	node(int value, int rem) : value(value), rem(rem), pre(NULL) { }
	node(int value, int rem, node *pre) : value(value), rem(rem), pre(pre) { }
}Node;

void output(Node *t) {
	if (t->pre == NULL) {
		cout << t->value;
		return ;
	}
	output(t->pre);
	cout << t->value;
}

void bfs(int n) {
	queue<Node> q;
	int rem;
	q.push(Node(0, 0));
	q.push(Node(1, 0));
	while (!q.empty()) {
		Node *tmp = new Node(q.front());
		q.pop();
		if ((rem = (tmp->rem*10 + tmp->value) % n) == 0 && !(tmp->value == 0 && tmp->rem == 0)) {
			output(tmp);
			return ;
		}
		if (!flag[rem] || (tmp->rem == 0)) {
			q.push(Node(0, rem, tmp));
			q.push(Node(1, rem, tmp));
			flag[rem] = true;
		}
	}
}

int main() {
	int n;
	while (true) {
		cin >> n;
		if (!n)
			break;
		memset(flag, false, sizeof(flag));
		bfs(n);
		cout << endl;
	}
	return 0;
}