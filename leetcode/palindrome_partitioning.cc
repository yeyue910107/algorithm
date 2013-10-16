#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> v;
        part(s, 0, s.size() - 1, v, res);
        return res;
    }
private:
    void part(string s, int i, int j, vector<string> &v, vector<vector<string>> &res) {
        if (i > j) {
            if (v.size() > 0)
                res.push_back(v);
            return;
        }
        for (int k = i; k <= j; k++) {
            if (is_palindrome(s, i, k)) {
                v.push_back(s.substr(i, k-i+1));
                part(s, k + 1, j, v, res);
                v.pop_back();
            }
        }
    }
    
    bool is_palindrome(string &s, int i, int j) {
        if (i < 0 || i >= s.size() || j < 0 || j >= s.size())
            return false;
        while (i < j) {
            if (s[i++] != s[j--])
                return false;
        }
        return true;
    }
};

int main() {
    string s = "abba";
    Solution so;
    vector<vector<string>> res;
    res = so.partition(s);
    return 0;
}
