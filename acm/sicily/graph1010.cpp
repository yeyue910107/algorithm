#include <stdio.h>
#include <vector>
#define MAX 100000
using namespace std;
struct ELink {
	int adjvex;
	ELink *next;
	ELink() {}
	ELink(int v, int w, ELink *next) : adjvex(v), next(next) {}
	ELink(int v, int w) : adjvex(v), next(NULL) {}
	ELink(int v) : adjvex(v), next(NULL) {}
};

struct VLink {
	int vertex, indegree;
	ELink *link, *end;
	VLink() {}
	VLink(int v) : vertex(v), link(NULL), indegree(0), end(NULL) {}
};

class Graph {
private:
	vector<VLink> table;
	int v_num, e_num;
	bool pushback_elink(const int, ELink *);
public:
	void create_graph(const int, const int);
	void topo_sort();
	Graph() { }
	Graph(const int &);
	Graph(const vector<VLink> &table, const int &v_num, const int &e_num) : table(table), v_num(v_num), e_num(e_num) { }
	~Graph() { }
};

Graph::Graph(const int& n) {
	int i;
	table.resize(n);
	v_num = n;
	e_num = 0;
	for (i = 0; i < n; i++) {
		VLink v(i);
		table[i] = v;
	}
}

bool Graph::pushback_elink(const int v, ELink* elink) {
	if (v < 0 || v >= v_num) {
		return false;
	}
	if (table[v].end == NULL) {
		table[v].link = elink;
		table[v].end = elink;
	}
	else {
		table[v].end->next = elink;
		table[v].end = elink;
	}
	return true;
}

int binary_search(const int s[], const int size, const int num) {
	int high = size - 1, low = 0, mid;
	while (low <= high) {
		mid = (high + low) / 2;
		if (num == s[mid])
			return mid;
		if (num < s[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

void adjust(int s[], const int size, const int i) {
	if (size > 0 && i >= 0 && i < size) {
		int j = 2 * i + 1, tmp = s[i];
		while (j < size) {
			if (j < size - 1 && s[j + 1] < s[j])
				j++;
			if (tmp > s[j]) {
				s[(j - 1) / 2] = s[j];
				j = 2 * j + 1;
			}
			else
				break;
		}
		s[(j - 1) / 2] = tmp;
		tmp = s[i];
		s[i] = s[size - 1];
		s[size - 1] = tmp;
	}
}

void Graph::topo_sort() {
	int no_in[MAX];
	int i, j, top = -1, size = 0, count = 0;
	for (i = v_num - 1; i >= 0; i--) {
		if (table[i].indegree == 0) {
			no_in[++top] = i;
		}
	}
	if (top == -1)
		return;
	while (!top >= 0 && count < v_num) {
		i = no_in[top--];
		printf("%d%c", i + 1, (count == v_num - 1) ? '\n' : ' ');
		if (table[i].link == NULL) {
			count++;
			continue;
		}
		ELink *e = table[i].link;
		while (e != NULL) {
			if (--table[e->adjvex].indegree == 0) {
				no_in[++top] = e->adjvex;
				for (j = top; j > 0 && e->adjvex > no_in[j - 1]; j--)
					no_in[j] = no_in[j - 1];
				no_in[j] = e->adjvex;
			}
			e = e->next;
		}
		count++;
	}
}

void Graph::create_graph(const int n, const int e) {
	int i, vi, vj;
	v_num = n;
	e_num = e;
	table.resize(n);
	for (i = 0; i < n; i++) {
		VLink v(i);
		table[i] = v;
	}
	for (i = 0; i < e; i++) {
		scanf("%d%d", &vi, &vj);
		ELink *ei = new ELink(vj - 1);
		pushback_elink(vi - 1, ei);
		table[vj - 1].indegree++;
	}
}

int main() {
	int num, n, e;
	Graph g;
	scanf("%d", &num);
	while (num-- > 0) {
		scanf("%d%d", &n, &e);
		g.create_graph(n, e);
		g.topo_sort();
	}
}

/*
1
7 8
1 3
1 4
2 4
2 5
3 6
3 7
4 7
5 7

2 2
1 2
2 1

2
5 5
3 4
4 1
3 2
2 4
5 3
7 8
1 3
1 4
2 4
2 5
3 6
3 7
4 7
5 7
*/