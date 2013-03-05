#include <stdio.h>
#include <vector>
#include <stack>

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
	ELink *link;
	VLink() {}
	VLink(int v, ELink *link) : vertex(v), link(link), indegree(0) {}
	VLink(int v) : vertex(v), link(NULL), indegree(0) {}
};

class Graph {
private:
	vector<VLink> table;
	int v_num, e_num;
	bool pushback_elink(const int, ELink *);
public:
	void create_graph(const int, const int);
	bool is_dag();
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
	ELink *e = table[v].link;
	if (table[v].link == NULL)
		table[v].link = elink;
	else {
		while (e->next != NULL)
			e = e->next;
		e->next = elink;
	}
	return true;
}

bool Graph::is_dag() {
	stack<int> no_in;
	int i, count = 0;
	for (i = 0; i < v_num; i++)
		if (table[i].indegree == 0)
			no_in.push(i);
	while (!no_in.empty() && count < v_num) {
		i = no_in.top();
		no_in.pop();
		if (table[i].link == NULL) {
			count++;
			continue;
		}
		ELink *e = table[i].link;
		while (e != NULL) {
			if (--table[e->adjvex].indegree == 0)
				no_in.push(e->adjvex);
			e = e->next;
		}
		count++;
	}
	return (count == v_num) ? true : false;
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
		//VLink v(vi - 1, ei);
		pushback_elink(vi - 1, ei);
		table[vj - 1].indegree++;
	}
}

int main() {
	int n, e;
	Graph g;
	scanf("%d%d", &n, &e);
	g.create_graph(n, e);
	printf("%d\n", (g.is_dag()) ? 1 : 0);
}

/*
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
*/