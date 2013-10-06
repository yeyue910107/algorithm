#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int>> res;
        if (n == 0 || k == 0 || k > n) return res;
        for (int i = 0; i < (1<<n); i++) {
            if (one_num(i) == k) {
                vector<int> one;
                for (int j = 0; j < n; j++) {
                    if ((i & (1<<j)) != 0)
                        one.push_back(j+1);
                }
                res.push_back(one);
            }
        }
        return res;
    }
private:
    int one_num(int num) {
        int k = 0;
        while (num != 0) {
            k++;
            num = num & (num - 1);
        }
        return k;
    }
};

int main() {
    vector<vector<int>> res;
    Solution s;
    res = s.combine(4, 2);
    return 0;
}
