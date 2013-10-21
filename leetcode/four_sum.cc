#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector<vector<int>> res;
        if (num.size() == 0) return res;
        sort(num.begin(), num.end());
        for (int i = 0; i < num.size(); i++) {
            if (i > 0 && num[i] == num[i - 1]) continue;
            for (int j = i + 1; j < num.size(); j++) {
                if (j > i + 1 && num[j] == num[j - 1]) continue;
                int remain = target - (num[i] + num[j]);
                int ii = j + 1, jj = num.size() - 1;
                while (ii < jj) {
                    int cur = num[ii] + num[jj];
                    if (cur == remain) {
                        vector<int> v;
                        v.push_back(num[i]);
                        v.push_back(num[j]);
                        v.push_back(num[ii]);
                        v.push_back(num[jj]);
                        res.push_back(v);
                        do {
                            ii++;
                            jj--;
                        } while (ii < jj && num[ii] == num[ii - 1] && num[jj] == num[jj + 1]);
                        if (ii >= jj) break;
                    }
                    else if (cur < remain) ii++;
                    else jj--;
                }
            }
        }
        return res;
    }
};

int main() {
    int a[] = {1, 0, -1, 0, -2, 2}, n = sizeof(a) / sizeof(int);
    vector<int> num;
    vector<vector<int>> res;
    for (int i = 0; i < n; i++)
        num.push_back(a[i]);
    Solution s;
    res = s.fourSum(num, 0);
    return 0;
}
