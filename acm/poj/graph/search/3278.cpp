#include<iostream>
#include<queue>

using namespace std;

enum { MAX = 300001 };
bool flag[MAX] = { false };
int depth[MAX] = { 0 };

int get_ans(int n, int m) {
	int tmp;
	queue<int> q;
	if (n == m)
		return 0;
	q.push(n);
	flag[n] = true;
	while (!q.empty()) {
		tmp = q.front();
		q.pop();
		if (tmp >= 0) {
			if (2 * tmp == m || tmp - 1 == m || tmp + 1 == m)
				return depth[tmp] + 1;
			if (tmp < m && !flag[2 * tmp]) {
				depth[2 * tmp] = depth[tmp] + 1;
				q.push(2 * tmp);
				flag[2 * tmp] = true;
			}
			if (tmp > 0 && !flag[tmp - 1]) {
				depth[tmp - 1] = depth[tmp] + 1;
				q.push(tmp - 1);
				flag[tmp - 1] = true;
			}
			if (tmp < m && !flag[tmp + 1]) {
				depth[tmp + 1] = depth[tmp] + 1;
				q.push(tmp + 1);
				flag[tmp + 1] = true;
			}
		}
	}
	return -1;
}

int main() {
	int n, m;

	cin >> n >> m;
	cout << get_ans(n, m) << endl;
}