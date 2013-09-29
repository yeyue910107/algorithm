#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <memory>

#define MAX 128
using namespace std;

class Solution {
public:
    int ladderLength(string start, string end, set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
	set<string>::iterator it;
	vector<string> vdic;
	int i;
	vdic.push_back(start);
	for (i = 1, it = dict.begin(); it != dict.end(); i++, it++) {
		vdic.push_back(*it);
	}
	vdic.push_back(end);
	int num = i + 1;
	vector<int> v[MAX];

	for (i = 0; i < num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (onlyOneLetterDiff(vdic[i], vdic[j])) {
				v[i].push_back(j);
				v[j].push_back(i);
			}
		}
	}

	return bfs(v, num - 1);
    }

private:
	bool onlyOneLetterDiff(string s, string t) {
		if (s.size() != t.size())
			return false;
		int i, num = 0;
		for (i = 0; i < s.size(); i++) {
			if (s[i] != t[i]) {
				if (++num > 1)
					return false;
			}
		}
		return true;
	}

	int bfs(vector<int> v[], int k) {
		queue<int> q, h;
		bool flag[MAX];
		memset(flag, false, MAX);
		q.push(0); h.push(1);
		while (!q.empty()) {
			int index = q.front(), height = h.front();
			q.pop(); h.pop();
			flag[index] = true;
			for (int i = 0; i < v[index].size(); i++) {
				if (!flag[v[index][i]]) {
					if (v[index][i] == k)
						return height+1;;
					q.push(v[index][i]);
					h.push(height+1);
				}
			}
		}
		return 0;
	}
};

int main() {
	string start("hit"), end("hog");
	//dict = ["hot","dot","dog","lot","log"]
	set<string> dict;
	dict.insert("hot");
	dict.insert("dot");
	dict.insert("dog");
	dict.insert("lot");
	dict.insert("log");
	Solution s;
	cout << s.ladderLength(start, end, dict) << endl;
	return 0;
}
