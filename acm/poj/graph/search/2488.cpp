#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct point {
	int x, y;
	point() {}
	point(int x, int y) : x(x), y(y) {}
}P;

enum { MAX = 8, LEN = 26};
bool flag[MAX][MAX] = { false };
int n, m, pa[MAX] = {-2, -2, -1, -1, 1, 1, 2, 2}, qa[MAX] = {-1, 1, -2, 2, -2, 2, -1, 1};
P path[LEN];

void output(P path[]) {
	for (int i = 0; i < n * m; i++)
		cout << (char)('A' + path[i].x) << (char)('1' + path[i].y);
	cout << endl;
}

bool get_ans(int p, int q, int len) {
	int px, qx;
	
	if (len == n*m)
		return true;
	for (int i = 0; i < MAX; i++) {
		px = p + pa[i]; qx = q + qa[i];
		if (px >= 0 && px < m && qx >= 0 && qx < n && !flag[px][qx]) {
			flag[px][qx] = true;
			if(get_ans(px, qx, len + 1)) {
				path[len].x = px;
				path[len].y = qx;
				return true;
			}
			flag[px][qx] = false;
		}
	}
	return false;
}

int main() {
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> n >> m;
		memset(flag, false, sizeof(flag));
		
		flag[0][0] = true;
		path[0].x = 0; path[0].y = 0;
		if (get_ans(0, 0, 1)) {
			cout << "Scenario #" << i + 1 << ":\n";
			output(path);
		}
		else 
			cout << "Scenario #" << i + 1 << ":\n" << "impossible\n";
		if (i != num - 1)
			cout << endl;

	}
	return 0;
}