#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Solution {
static const int MAX = 256;
public:
    vector<int> findSubstring(string S, vector<string> &L) {
		int len = L[0].size(), size = L.size(), start = 0;
		
		map<string, int> words;
		map<string, int>::iterator it;
		vector<int> res;
		int count[MAX];
		memset(count, 0, sizeof(count));
		for (int i = 0; i < size; i++) {
			if (words.find(L[i]) == words.end()) {
				words.insert(pair<string, int>(L[i], i));
				count[i]++;
			}
			else count[words[L[i]]]++;
		}
		int i = 0;
		while (i < S.size()) {
			if (is_concat(S, i, size, len, L, words, count))
				res.push_back(i);
			i++;
		}
		return res;
    }
private:
	bool is_concat(string S, const int start, const int size, const int len, vector<string> &L, map<string, int> &words, int count[]) {
		int i = start, ssize = S.size(), end = start + size*len;
		int flag[MAX];
		if (end > ssize)
			return false;
		string str;
		map<string, int>::iterator it;
		memset(flag, 0, sizeof(flag));
		while (i < end) {
			str = S.substr(i, len);
			it = words.find(str);
			if (it == words.end() || flag[it->second] >= count[it->second])
				return false;
			flag[it->second]++;
			i += len;
		}
		return true;
	}
};

int main() {
	string S = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
	//string S = "barfoothefoobarman";
	//string T[2] = {"foo", "bar"};
	string T[5] = {"fooo","barr","wing","ding","wing"};
	vector<string> L;
	for (int i = 0; i < 5; i++)
		L.push_back(T[i]);
	vector<int> res;
	Solution s;
	res = s.findSubstring(S, L);
	return 0;
}
