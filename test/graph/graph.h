#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#define MAX 128

using namespace std;
struct ELink {
	int adjvex, weight;
	ELink *next;
	ELink() {}
	ELink(int v, int w, ELink *next) : adjvex(v), weight(w), next(next) {}
	ELink(int v, int w) : adjvex(v), weight(w), next(NULL) {}
	ELink(int v) : adjvex(v), weight(0), next(NULL) {}
};

struct VLink {
	int vertex;
	ELink *link;
	VLink() {}
	VLink(int v, ELink *link) : vertex(v), link(link) {}
	VLink(int v) : vertex(v), link(NULL) {}
};

class Graph {
private:
	vector<VLink> table, edges;
	int v_num, e_num;
	void visit(const int) const;
	ELink *get_elink(const int, const int) const;
	bool pushback_elink(const int, ELink *);
	bool popback_elink(const int);
	int get_elinks_num(const int) const;
	void print_edges();
public:
	void travel_dfs();
	void travel_bfs();
	void dfs(const int, vector<bool> &);
	void bfs(const int, vector<bool> &);
	void get_connection_component(void (Graph::*fun)(const int, vector<bool> &));
	void create_graph(const int, const int);
	void minspant_prim() const;
	void minspant_kruskal() const;
	bool has_circuit() const;
	void dijkstra(const int) const;
	Graph() { }
	Graph(const int &);
	Graph(const vector<VLink> &table, const int &v_num, const int &e_num) : table(table), v_num(v_num), e_num(e_num) { }
	~Graph() { }
};

#endif