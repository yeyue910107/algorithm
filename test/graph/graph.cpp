#include "graph.h"

using namespace std;

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

void Graph::visit(const int v) const {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
		return;
	}
	cout << "vertex " << v << endl;
}

ELink *Graph::get_elink(const int v, const int i) const {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
		return NULL;
	}
	if (table[v].link == NULL) {
		cout << "no elinks of vertex " << v << endl;
		return NULL;
	}
	ELink *e = table[v].link;
	for (; e != NULL; e = e->next)
		if (e->adjvex == i)
			break;
	return e;
}

bool Graph::pushback_elink(const int v, ELink* elink) {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
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

bool Graph::popback_elink(const int v) {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
		return false;
	}
	if (table[v].link == NULL)
		return false;
	ELink *e = table[v].link;
	if (e->next == NULL) {
		table[v].link = NULL;
		return true;
	}
	while (e->next->next != NULL)
		e = e->next;
	delete e->next;
	e->next = NULL;
	return true;
}

int Graph::get_elinks_num(const int v) const {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
		return -1;
	}
	if (table[v].link == NULL) {
		return 0;
	}
	ELink *e = table[v].link;
	int count;
	for (count = 1; e->next != NULL; e = e->next, count++)
		;
	return count;
}

void Graph::print_edges() {
	int i;
	for(i = 0; i < e_num; i++)
		cout << "vertex: " << edges[i].vertex << " vertex: " << edges[i].link->adjvex << " weight: " << edges[i].link->weight << endl;
}

void Graph::travel_dfs() {
	vector<bool> flag;
	int i;
	for (i = 0;i < v_num; i++)
		flag.push_back(false);
	for (i = 0; i < v_num; i++) {
		if (!flag[i])
			dfs(i, flag);
	}
}

void Graph::travel_bfs() {
	vector<bool> flag;
	int i;
	for (i = 0;i < v_num; i++)
		flag.push_back(false);
	for (i = 0; i < v_num; i++) {
		if (!flag[i])
			bfs(i, flag);
	}
}

void Graph::get_connection_component(void (Graph::*fun)(const int, vector<bool> &)) {
	vector<bool> flag;
	int i, count = 0;
	for (i = 0;i < v_num; i++)
		flag.push_back(false);
	for (i = 0; i < v_num; i++) {
		if (!flag[i]) {
			printf("component %d:\n", ++count);
			(this->*fun)(i, flag);
		}
	}
	printf("total components v_number is %d.\n", count);
}

void Graph::dfs(const int i, vector<bool> &flag) {
	visit(i);
	flag[i] = true;
	ELink *e = table[i].link;
	do {
		if (!flag[e->adjvex])
			dfs(e->adjvex, flag);
		e = e->next;
	}
	while (e != NULL);
}

bool Graph::has_circuit() const {
	int i, _enum = e_num, _vnum = v_num, count = 0;
	vector<int> elinks_num;
	if (_enum >= _vnum)
		return true;
	for (i = 0; i < v_num; i++)
		elinks_num.push_back(get_elinks_num(i));
	for (i = 0; i < v_num; i++) {
		if (elinks_num[i] == 0)
			_vnum--;
		else if (elinks_num[i] == 1) {
			_vnum--;
			elinks_num[i]--;
			elinks_num[table[i].link->adjvex]--;
		}
	}
	for (i = 0, _enum = 0; i < v_num; i++)
		_enum += elinks_num[i];
	_enum /= 2;
	if (_vnum > 0 && _enum >= _vnum)
		return true;
	return false;
}

void Graph::bfs(const int i, vector<bool> &flag) {
	if (i < 0 || i >= v_num) {
		cout << "vertex " << i << "out of index." << endl;
		return ;
	}
	queue<int> q;
	int index, cur = i;
	//cout << table[i][0] << endl;
	//flag[i] = true;
	q.push(i);
	ELink *e;
	while (!q.empty()) {
		index = q.front();
		q.pop();
		visit(index);
		flag[index] = true;
		e = table[index].link;
		while (e != NULL) {
			cur = e->adjvex;
			if (!flag[cur]) {
				//visit(cur);
				flag[cur] = true;
				if (cur != index)
					q.push(cur);
			}
			e = e->next;
		}
	}
}

void Graph::create_graph(const int n, const int e) {
	int i, vi, vj, weight;
	v_num = n;
	e_num = e;
	table.resize(n);
	edges.resize(e);
	for (i = 0; i < n; i++) {
		VLink v(i);
		table[i] = v;
	}
	for (i = 0; i < e; i++) {
		scanf("%d%d%d", &vi, &vj, &weight);
		ELink *ei = new ELink(vj, weight);
		ELink *ej = new ELink(vi, weight);
		VLink v(vi, ei);
		this->pushback_elink(vi, ei);
		this->pushback_elink(vj, ej);
		edges[i] = v;
	}
}

void Graph::minspant_prim() const {
	vector<int> lowcost, end;
	const int MAXVALUE = 1024;
	int i, j, min, mincost;
	ELink *tmp = NULL;
	lowcost.push_back(0);
	end.push_back(0);
	for (i = 1; i < v_num; i++) {
		end.push_back(0);
		tmp = get_elink(0, i);
		lowcost.push_back((tmp == NULL) ? MAXVALUE : tmp->weight);
	}
	for (i = 1; i < v_num; i++) {
		mincost = MAXVALUE;
		for (j = 0; j < v_num; j++) {
			if (lowcost[j] != 0 && lowcost[j] < mincost) {
				mincost = lowcost[j];
				min = j;
			}
		}
		cout << "one edge of the minspant is: vertex " << end[min] << ", vertex " << min << ", weight " << mincost << endl;
		lowcost[min] = 0;
		//end[min] = i;
		for (j = 0; j < v_num; j++) {
			if (lowcost[j] != 0) {
				tmp = get_elink(min, j);
				if (tmp != NULL && tmp->weight < lowcost[j]) {
					lowcost[j] = tmp->weight;
					end[j] = min;
				}
			}
		}
	}
}

void Graph::minspant_kruskal() const {
	Graph kruskal(v_num);
	vector<bool> flag;
	const int MAXVALUE = 1024;
	int i, mincost, mini;
	VLink min;
	for (i = 0; i < e_num; i++)
		flag.push_back(false);
	while (kruskal.e_num < v_num - 1) {
		for (i = 0, mincost = MAXVALUE; i < e_num; i++) {
			if (!flag[i] && edges[i].link->weight < mincost) {
				mincost = edges[i].link->weight;
				min = edges[i];
				//flag[j] = true;
				mini = i;
			}
		}
		ELink *elink1 = new ELink(min.link->adjvex, min.link->weight);
		kruskal.pushback_elink(min.vertex, elink1);
		ELink *elink2 = new ELink(min.vertex, min.link->weight);
		kruskal.pushback_elink(min.link->adjvex, elink2);
		kruskal.e_num++;
		flag[mini] = true;
		if (kruskal.has_circuit()) {
			kruskal.popback_elink(min.vertex);
			kruskal.popback_elink(min.link->adjvex);
			kruskal.e_num--;
		}
		else {
			VLink v(min.vertex, elink1);
			kruskal.edges.push_back(v);
		}
	}
	kruskal.print_edges();
}

void Graph::dijkstra(const int v) const {
	if (v < 0 || v >= v_num) {
		cout << "vertex " << v << "out of index." << endl;
		return ;
	}
	vector<int> dist;
	vector<bool> flag;
	vector<vector<int>> path;
	const int MAXVALUE = 1024;
	int i, j, mincost = MAXVALUE, min = 0;
	path.resize(v_num);
	for (i = 0; i < v_num; i++) {
		dist.push_back(MAXVALUE);
		flag.push_back(false);
		path[i].push_back(v);
	}
	dist[v] = 0;
	flag[v] = true;

	if (table[v].link == NULL)
		return;
	ELink *e = table[v].link;
	while (e != NULL) {
		dist[e->adjvex] = e->weight;
		e = e->next;
	}

	for (i = 1; i < v_num; i++) {
		for (j = 0, min = -1, mincost = MAXVALUE; j < v_num; j++) {
			if (j != v && !flag[j] && dist[j] <= mincost) {
				mincost = dist[j];
				min = j;
			}
		}
		if (min == -1)
			break;
		path[min].push_back(min);
		flag[min] = true;

		if (table[min].link == NULL)
			continue;
		ELink *emin = table[min].link;
		while (emin != NULL) {
			if (!flag[emin->adjvex]) {
				if (emin->weight + dist[min] < dist[emin->adjvex]) {
					dist[emin->adjvex] = emin->weight + dist[min];
					path[emin->adjvex].resize(path[min].size());
					for (j = 0; j < path[emin->adjvex].size(); j++)
						path[emin->adjvex][j] = path[min][j];
				}
			}
			emin = emin->next;
		}
	}

	cout << "From vertex " << v << ":" << endl;
	for (i = 0; i < v_num; i++) {
		if (i != v) {
			cout << "to vertex " << i << ": shortest path : ";
			for (j = 0; j < path[i].size(); j++)
				cout << path[i][j] << ((j == path[i].size() - 1) ? " distance : " : "->");
			cout << dist[i] << endl;
		}
	}
}

int main() {
	int n = 7, e = 9;
	Graph g;
	g.create_graph(n, e);
	//g.travel_dfs();
	//g.travel_bfs();
	g.get_connection_component(&Graph::bfs);
	//g.minspant_kruskal();
	g.dijkstra(0);
}
/*
0 1 0
0 2 0
0 3 0
1 3 0
2 3 0
2 4 0
3 4 0
5 6 0
5 8 0
6 7 0
7 8 0

0 1 16
0 2 20
0 3 19
1 2 11
1 4 6
1 5 5
2 3 22
2 4 14
3 4 18
4 5 9

0 1 10
0 2 2
1 4 1
2 3 2
2 5 11
3 4 4
3 5 6
4 6 7
5 6 3
*/