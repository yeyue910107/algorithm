#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> v;
        string pattern = "/";
        path += pattern;
        int i = 0, pos;
        while (i < path.size() && (pos = path.find(pattern, i)) >= 0) {
            string tmp = path.substr(i, pos - i);
            if (tmp == "..") {
                if (v.size() > 0)
                    v.pop_back();
            }
            else if (tmp.size() > 0 && tmp != ".") {
                v.push_back(tmp);
            }
            i = pos + 1;
        }
        if (v.size() == 0) return pattern;
        string res = "";
        for (int i = 0; i < v.size(); i++){
            res += pattern + v[i];
        }
        return res;
    }
};

int main() {
    string path = "/a/./b/../../c/";
    //string path = "/home/";
    //string path = "/../..";
    Solution s;
    string res = s.simplifyPath(path);
    return 0;
}
