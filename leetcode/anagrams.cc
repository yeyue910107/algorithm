#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

using namespace std;

/*int cmp(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}*/

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        int size = strs.size();
        vector<string> res;
        string tmp;
        map<string, int> dic;
        map<string, int>::iterator it;
        for (int i = 0; i < size; i++) {
            tmp = strs[i];
	    sort(tmp.begin(), tmp.end());
            it = dic.find(tmp);
            if (it == dic.end())
                dic.insert(pair<string, int>(tmp, i));
            else {
                if (it->second != -1) {
                    res.push_back(strs[it->second]);
                    dic[tmp] = -1;
                }
                res.push_back(strs[i]);
            }
        }
        return res;
    }
/*private:
    char *strSort(const string s) {
        int len = s.size();
        char *res = new char[len+1];
		strcpy_s(res, len+1, s.c_str());
        qsort(res, len, sizeof(*res), cmp);
        return res;
    }*/
};

int main() {
	string s[5] = {"", "", "def", "efd", "bn"};
	vector<string> str, res;
	for (int i = 0; i < 5; i++)
		str.push_back(s[i]);
	Solution so;
	res = so.anagrams(str);
	return 0;
}
