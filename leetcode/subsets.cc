#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &S) {
        vector<vector<int>> res;
        int size = S.size();
        if (size == 0) return res;
        sort(S.begin(), S.end());
        for (int i = 0; i < (1<<size); i++) {
            vector<int> one;
            bool flag = false;
            for (int j = 0; j < size; j++) {
                if ((i & (1<<j)) != 0) {
                    if (j > 0 && S[j] == S[j - 1] && (i & (1<<(j-1))) == 0) {
                        flag = true;
                        break;
                    }
                    one.push_back(S[j]);
                }
            }
            if (flag)
                continue;
            res.push_back(one);
        }
        return res;
    }

    vector<vector<int>> subsets(vector<int> &S) {
        vector<vector<int>> res;
        int size = S.size();
        if (size == 0) return res;
        sort(S.begin(), S.end());
        for (int i = 0; i < (1<<size); i++) {
            vector<int> one;
            for (int j = 0; j < size; j++) {
                if ((i & (1<<j)) != 0)
                    one.push_back(S[j]);
            }
            res.push_back(one);
        }
        return res;
    }
};

int main() {
    int a[3] = {1, 2, 2};
    vector<int> S;
    for (int i = 0; i < 3; i++)
        S.push_back(a[i]);
    vector<vector<int>> res;
    Solution s;
    res = s.subsetsWithDup(S);
    return 0;
}
