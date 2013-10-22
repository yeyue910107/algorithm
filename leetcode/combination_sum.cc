#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {

public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        if (candidates.size() == 0) return res;
        can.clear();
        sort(candidates.begin(), candidates.end());
        for (int i = 0; i < candidates.size(); i++) {
            if (i > 0 && candidates[i] == candidates[i - 1]) continue;
            can.push_back(candidates[i]);
        }
        num.resize(can.size(), 0);
        int n = target;
        comb(0, n, res);
        return res;
    }
private:
    vector<int> num, can;

    void comb(const int i, int n, vector<vector<int>> &res) {
        if (i >= can.size()) return;
        num[i] = n / can[i];
        n %= can[i];
        if (n == 0) {
            vector<int> v;
            for (int j = 0; j <= i; j++) {
                for (int k = 1; k <= num[j]; k++)
                    v.push_back(can[j]);
            }
            res.push_back(v);
        }
        
        while (num[i] > 0) {
            num[i]--;
            n += can[i];
            comb(i + 1, n, res);
        } 
    }
};

int main() {
    int a[] = {1, 2}, n = sizeof(a) / sizeof(int);
    vector<int> num;
    vector<vector<int>> res;
    for (int i = 0; i < n; i++)
        num.push_back(a[i]);
    Solution s;
    res = s.combinationSum(num, 100);
    return 0;
}
