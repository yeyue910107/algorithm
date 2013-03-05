/*#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
enum {MAX = 102, INF = 65535, STATE = 205};

void get_complement(set<int> s[MAX], set<int> t[MAX], const int num) {
	int i, j;
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			if (j != i && (!s[i].count(j) || !s[j].count(i))) {
				t[i].insert(j);
				t[j].insert(i);
			}
		}
	}
}

bool dfs(set<int> t[MAX], vector<bool> &flag, const int v, const int num, set<int> m[MAX][2], const int cnum, int group) {
	set<int>::iterator i;

	if (m[cnum][group^1].count(v))
		return false;
	m[cnum][group].insert(v);
	for (i = t[v].begin(); i != t[v].end(); i++) {
		if (m[cnum][group].count(*i))
			return false;
		m[cnum][group^1].insert(*i);
	}
	flag[v] = true;
	for (i = t[v].begin(); i != t[v].end(); i++) {
		if (!flag[*i]) {
			if (!dfs(t, flag, *i, num, m, cnum, group^1))
				return false;
		}
	}
	return true;
}

int get_component(set<int> t[MAX], set<int> m[MAX][2], const int num) {
	vector<bool> flag;
	int i, count = 0;
	for (i = 0; i < num; i++)
		flag.push_back(false);
	for (i = 0; i < num; i++) {
		if (!flag[i]) {
			if (!dfs(t, flag, i, num, m, count++, 0))
				return 0;
		}
	}
	return count;
}

void get_ans(set<int> m[MAX][2], const int num, const int cnum) {
	bool dp[MAX][STATE] = { false };
	int path[MAX][STATE][3] = {0};
	vector<int> s[2];
	int i, j, size0 = m[0][0].size(), size1 = m[0][1].size(), ans = INF;
	set<int>::iterator iter;
	for (j = 0; j < num * 2; j++) {
		if (j == size0 - size1 + num || j == size1 - size0 + num)
			dp[0][j] = true;
		else
			dp[0][j] = false;
	}
	path[0][size1 - size0 + num][0] = 1;
	path[0][size0 - size1 + num][1] = 1;
	for (i = 1; i < cnum; i++) {
		for (j = 0; j < num * 2; j++) {
			if (dp[i - 1][j]) {
				size0 = m[i][0].size();
				size1 = m[i][1].size();
				dp[i][j + size0 - size1] = true;
				dp[i][j + size1 - size0] = true;
				path[i][j + size0 - size1][1] = 1;
				path[i][j + size1 - size0][0] = 1;
				path[i][j + size0 - size1][2] = path[i][j + size1 - size0][2] = j;
			}
		}
	}
	for (i = 0; i < num * 2; i++) {
		if (dp[cnum - 1][i] && abs(ans - num) > abs(i - num))
			ans = i;
	}
	for (i = cnum - 1; i >= 0; i--) {
		int k = path[i][ans][0];
		ans = path[i][ans][2];
		for (iter = m[i][0].begin(); iter != m[i][0].end(); iter++)
			s[k].push_back(*iter);
		for (iter = m[i][1].begin(); iter != m[i][1].end(); iter++)
			s[k^1].push_back(*iter);
	}
	size0 = s[0].size(); size1 = s[1].size();
	cout << size0 << ' ';
	for (i = 0; i < size0; i++) {
		cout << s[0][i] + 1 << ((i == size0 - 1) ? '\n' : ' ');
	}
	cout << size1 << ' ';
	for (i = 0; i < size1; i++) {
		cout << s[1][i] + 1 << ((i == size1 - 1) ? '\n' : ' ');
	}
}

int main() {
	int num, tmp, cnum;
	set<int> s[MAX], t[MAX];
	set<int> m[MAX][2];
	cin >> num;
	for (int i = 0; i < num; i++) {
		while (1) {
			cin >> tmp;
			if (tmp == 0)
				break;
			s[i].insert(tmp - 1);
		}
	}
	get_complement(s, t, num);
	if (!(cnum = get_component(t, m, num)))
		cout << "No solution" << endl;
	else
		get_ans(m, num, cnum);
	return 0;
}*/

/*#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
enum {MAX = 105, INF = 65535, STATE = 210};

void get_complement(int s[][MAX], set<int> t[MAX], const int num) {
	int i, j;
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			if (j != i && (!s[i][j] || !s[j][i])) {
				t[i].insert(j);
				t[j].insert(i);
			}
		}
	}
}

bool dfs(set<int> t[MAX], vector<bool> &flag, const int v, const int num, set<int> m[MAX][2], const int cnum, int group) {
	set<int>::iterator i;

	if (m[cnum][group^1].count(v))
		return false;
	m[cnum][group].insert(v);
	for (i = t[v].begin(); i != t[v].end(); i++) {
		if (m[cnum][group].count(*i))
			return false;
		m[cnum][group^1].insert(*i);
	}
	flag[v] = true;
	for (i = t[v].begin(); i != t[v].end(); i++) {
		if (!flag[*i]) {
			if (!dfs(t, flag, *i, num, m, cnum, group^1))
				return false;
		}
	}
	return true;
}

int get_component(set<int> t[MAX], set<int> m[MAX][2], const int num) {
	vector<bool> flag;
	int i, count = 0;
	for (i = 0; i < num; i++)
		flag.push_back(false);
	for (i = 0; i < num; i++) {
		if (!flag[i]) {
			if (!dfs(t, flag, i, num, m, count++, 0))
				return 0;
		}
	}
	return count;
}

int cmp(const void *a, const void *b) {
	if ((int)a > (int)b)
		return 1;
	return -1;
}

void get_ans(set<int> m[MAX][2], const int num, const int cnum) {
	bool dp[MAX][STATE] = { false };
	int path[MAX][STATE][3] = {0};
	vector<int> s[2];
	int i, j, size0 = m[0][0].size(), size1 = m[0][1].size(), ans = INF;
	set<int>::iterator iter;

	dp[0][size0 - size1 + num] = true;
	dp[0][size1 - size0 + num] = true;
	path[0][size1 - size0 + num][0] = 1;
	path[0][size0 - size1 + num][1] = 1;
	for (i = 1; i < cnum; i++) {
		for (j = 0; j < num * 2; j++) {
			if (dp[i - 1][j]) {
				size0 = m[i][0].size();
				size1 = m[i][1].size();
				dp[i][j + size0 - size1] = true;
				dp[i][j + size1 - size0] = true;
				path[i][j + size0 - size1][1] = 1;
				path[i][j + size0 - size1][0] = 0;
				path[i][j + size1 - size0][1] = 0;
				path[i][j + size1 - size0][0] = 1;
				path[i][j + size0 - size1][2] = path[i][j + size1 - size0][2] = j;
			}
		}
	}
	for (i = 0; i < num * 2; i++) {
		if (dp[cnum - 1][i] && abs(ans - num) >= abs(i - num))
			ans = i;
	}
	for (i = cnum - 1; i >= 0; i--) {
		int k = path[i][ans][0];
		
		for (iter = m[i][0].begin(); iter != m[i][0].end(); iter++)
			s[k].push_back(*iter);
		for (iter = m[i][1].begin(); iter != m[i][1].end(); iter++)
			s[k^1].push_back(*iter);
		ans = path[i][ans][2];
	}
	size0 = s[0].size(); size1 = s[1].size();
	cout << size0 << ' ';
	for (i = 0; i < size0; i++) {
		cout << s[0][i] + 1 << ((i == size0 - 1) ? '\n' : ' ');
	}
	cout << size1 << ' ';
	for (i = 0; i < size1; i++) {
		cout << s[1][i] + 1 << ((i == size1 - 1) ? '\n' : ' ');
	}
}

int main() {
	int num, tmp, cnum;
	int s[MAX][MAX] = {0};
	set<int> t[MAX];
	set<int> m[MAX][2];
	cin >> num;
	for (int i = 0; i < num; i++) {
		while (1) {
			cin >> tmp;
			if (tmp == 0)
				break;
			s[i][tmp - 1] = 1;
		}
	}
	get_complement(s, t, num);
	if (!(cnum = get_component(t, m, num)))
		cout << "No solution" << endl;
	else
		get_ans(m, num, cnum);
	return 0;
}*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
enum {MAX = 105, INF = 65535, STATE = 210};

void get_complement(bool s[][MAX], bool t[][MAX], const int num) {
	int i, j;
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			if (j != i && (!s[i][j] || !s[j][i])) {
				t[i][j] = t[j][i] = true;
			}
		}
	}
}

bool dfs(bool t[][MAX], vector<bool> &flag, const int v, const int num, set<int> m[MAX][2], const int cnum, int group) {
	int i;

	if (m[cnum][group^1].count(v))
		return false;
	m[cnum][group].insert(v);
	for (i = 0; i < num; i++) {
		if (t[v][i]) {
			if (m[cnum][group].count(i))
				return false;
			m[cnum][group^1].insert(i);
		}
	}
	flag[v] = true;
	for (i = 0; i < num; i++) {
		if (t[v][i]) {
			if (!flag[i]) {
				if (!dfs(t, flag, i, num, m, cnum, group^1))
					return false;
			}
		}
	}
	return true;
}

int get_component(bool t[][MAX], set<int> m[MAX][2], const int num) {
	vector<bool> flag;
	int i, count = 0;
	for (i = 0; i < num; i++)
		flag.push_back(false);
	for (i = 0; i < num; i++) {
		if (!flag[i]) {
			if (!dfs(t, flag, i, num, m, count++, 0))
				return 0;
		}
	}
	return count;
}

void get_ans(set<int> m[MAX][2], const int num, const int cnum) {
	bool dp[MAX][STATE] = { false };
	int path[MAX][STATE][3] = {0};
	vector<int> s[2];
	int i, j, size0 = m[0][0].size(), size1 = m[0][1].size(), ans = INF;
	set<int>::iterator iter;

	dp[0][size0 - size1 + num] = true;
	dp[0][size1 - size0 + num] = true;
	path[0][size1 - size0 + num][0] = 1;
	path[0][size0 - size1 + num][1] = 1;
	for (i = 1; i < cnum; i++) {
		for (j = 0; j < num * 2; j++) {
			if (dp[i - 1][j]) {
				size0 = m[i][0].size();
				size1 = m[i][1].size();
				dp[i][j + size0 - size1] = true;
				dp[i][j + size1 - size0] = true;
				path[i][j + size0 - size1][1] = 1;
				path[i][j + size0 - size1][0] = 0;
				path[i][j + size1 - size0][1] = 0;
				path[i][j + size1 - size0][0] = 1;
				path[i][j + size0 - size1][2] = path[i][j + size1 - size0][2] = j;
			}
		}
	}
	for (i = 0; i < num * 2; i++) {
		if (dp[cnum - 1][i] && abs(ans - num) >= abs(i - num))
			ans = i;
	}
	for (i = cnum - 1; i >= 0; i--) {
		int k = path[i][ans][0];
		
		for (iter = m[i][0].begin(); iter != m[i][0].end(); iter++)
			s[k].push_back(*iter);
		for (iter = m[i][1].begin(); iter != m[i][1].end(); iter++)
			s[k^1].push_back(*iter);
		ans = path[i][ans][2];
	}
	size0 = s[0].size(); size1 = s[1].size();
	cout << size0 << ' ';
	for (i = 0; i < size0; i++) {
		cout << s[0][i] + 1 << ((i == size0 - 1) ? '\n' : ' ');
	}
	cout << size1 << ' ';
	for (i = 0; i < size1; i++) {
		cout << s[1][i] + 1 << ((i == size1 - 1) ? '\n' : ' ');
	}
}

int main() {
	int num, tmp, cnum;
	bool s[MAX][MAX] = { false }, t[MAX][MAX] = { false };
	set<int> m[MAX][2];
	cin >> num;
	for (int i = 0; i < num; i++) {
		while (1) {
			cin >> tmp;
			if (tmp == 0)
				break;
			s[i][tmp - 1] = true;
		}
	}
	get_complement(s, t, num);
	if (!(cnum = get_component(t, m, num)))
		cout << "No solution" << endl;
	else
		get_ans(m, num, cnum);
	return 0;
}