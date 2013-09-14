#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
const int N = 256, MAX = 128;
int n, size;

bool g[N][N];
int color[N];

bool dfs(int v, int c) {
	color[v] = c;
	for (int i = 0; i < size; i++) {
		if (v != i && g[v][i]) {
			if (color[i] == 0) {
				if (!dfs(i, -c))
					return false;
			}
			else if (color[v] == color[i])
				return false;
		}
	}
	return true;
}

int main() {
	fstream in, out;
	in.open("test.txt", ios::in);
	out.open("out.txt", ios::out);
	int x, y, count = 0;
	int num;
	string s, t;
	in >> num;
	for (int i = 1; i <= num; i++) {
		memset(g, false, sizeof(g));
		map<string, int> _map;
		map<string, int>::iterator it;
		count = 0; size = 0;
		in >> n;
		for (int j = 0; j < n; j++) {
			in >> s >> t;
			it = _map.find(s);
			if (it == _map.end()) {
				_map.insert(pair<string, int>(s, size));
				x = size++;
			}
			else x = it->second;
			it = _map.find(t);
			if (it == _map.end()) {
				_map.insert(pair<string, int>(t, size));
				y = size++;
			}
			else y = it->second;
			g[x][y] = true;
			g[y][x] = true;
		}
		memset(color, 0, sizeof(color));
		bool flag = true;
		for (int j = 0; j < size; j++) {
			if (color[j] != 0)
				continue;
			flag = dfs(j, 1);
			if (!flag)
				break;
		}
		out << "Case #" << i << ": " << (flag ? "Yes" : "No") << "\r\n";
	}
	in.close();
	out.close();
	
    return 0;
}
