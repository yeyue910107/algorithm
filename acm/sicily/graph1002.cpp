#include <stdio.h>
#include <vector>

using namespace std;

class Graph {
private:
	std::vector<vector<int> > table;
	int num;
	
public:
	void dfs(const int, vector<bool> &);
	void get_connection_component();
	void create_graph(const int, const int);
	Graph() { }
	Graph(const vector<vector<int> > &table, const int &num) : table(table), num(num){ }
	~Graph() { }
};

void Graph::get_connection_component() {
	vector<bool> flag;
	int i, count = 0;
	for (i = 0;i < num; i++)
		flag.push_back(false);
	for (i = 0; i < num; i++) {
		if (!flag[i]) {
			//printf("component %d:\n", ++count);
			++count;
			dfs(i, flag);
		}
	}
	printf("%d\n", count);
}

void Graph::dfs(const int i, vector<bool> &flag) {
	//cout << table[i][0] << endl;
	flag[i] = true;
	vector<int>::iterator iter;
	for (iter = table[i].begin(); iter != table[i].end(); iter++) {
		if (!flag[*iter])
			dfs(*iter, flag);
	}
}

void Graph::create_graph(const int n, const int e) {
	int i, vi, vj;
	num = n;
	table.resize(n);
	for (i = 0; i < n; i++)
		table[i].push_back(i);
	for (i = 0; i < e; i++) {
		scanf("%d%d", &vi, &vj);
		table[vi - 1].push_back(vj - 1);
		table[vj - 1].push_back(vi - 1);
	}
}

int main() {
	int n, e;
	Graph g;
	scanf("%d%d", &n, &e);
	g.create_graph(n, e);
	//g.travel_dfs();
	//g.travel_bfs();
	g.get_connection_component();
}