#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Solution {

public:
    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        if (candidates.size() == 0) return res;
        sort(candidates.begin(), candidates.end());
        can.clear();
        _map.clear();
        for (int i = 0; i < candidates.size(); i++) {
            if (_map.find(candidates[i]) == _map.end()) {
                _map.insert(pair<int, int>(candidates[i], 1));
                can.push_back(candidates[i]);
            }
            else
                _map[candidates[i]]++;
        }
        num.resize(_map.size(), 0);
        int n = target;
        comb(0, n, res);
        return res;
    }
private:
    vector<int> num, can;
    map<int, int> _map;

    void comb(const int i, int n, vector<vector<int>> &res) {
        int tmp = _map[can[i]];
        num[i] = min(n / can[i], tmp);
        n -= num[i] * can[i];
        if (n == 0) {
            vector<int> v;
            for (int j = 0; j <= i; j++) {
                for (int k = 1; k <= num[j]; k++)
                    v.push_back(can[j]);
            }
            res.push_back(v);
        }
        if (i + 1 >= num.size()) return ;
        if (n >= can[i + 1])
            comb(i + 1, n, res);
        while (num[i] > 0) {
            num[i]--;
            n += can[i];
            if (n >= can[i + 1])
                comb(i + 1, n, res);
        } 
    }
};

int main() {
    int a[] = {1,1,1,1,2,2,2}, n = sizeof(a) / sizeof(int);
    vector<int> num;
    vector<vector<int>> res;
    for (int i = 0; i < n; i++)
        num.push_back(a[i]);
    Solution s;
    res = s.combinationSum2(num, 8);
    return 0;
}
