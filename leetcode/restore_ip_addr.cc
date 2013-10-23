#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
static const int MAX = 255;
public:
    vector<string> restoreIpAddresses(string s) {
        split.clear();
        res.clear();
        if (s.size() < 4 && s.size() > 12) return res;
        dfs(s, 4, 0);
        return res;
    }
private:
    vector<int> split;
    vector<string> res;
    void dfs(string s, const int num, const int i) {
        if (i >= s.size() || s.size() - i > num * 3)
            return ;
        if (num == 1) {
            int last = atoi(s.substr(i, s.size() - i).c_str());
            if (last > MAX || (last < 10 && s.size() - i > 1) || (last < 100 && s.size() - i > 2)) return ;
            assert(split.size() == 3);
            string tmp(s.substr(0, split[0] + 1));
            tmp += "." + s.substr(split[0] + 1, split[1] - split[0]);
            tmp += "." + s.substr(split[1] + 1, split[2] - split[1]);
            tmp += "." + s.substr(split[2] + 1, s.size() - split[2] - 1);
            res.push_back(tmp);
            return ;
        }
        int n = 0, j = 0;
        while (i + j < s.size() && j < 3 && n <= MAX) {
            n = n * 10 + s[i + j] - '0';
            if (n > MAX || (n < 10 && j > 0)) break;
            split.push_back(i + j);
            dfs(s, num - 1, i + j + 1);
            split.pop_back();
            j++;
        }
    }
};

int main() {
    string s = "010010";
    Solution so;
    vector<string> res;
    res = so.restoreIpAddresses(s);
    return 0;
}
