#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        if (height.size() == 0) return 0;
        int res = 0;
        for (int i = height.size() - 1; i >= 0; i--) {
            if (i != height.size() - 1 && height[i] <= height[i+1])
                continue;
            int _min = height[i];
            for (int j = i; j >= 0; j--) {
                _min = min(_min, height[j]);
                res = max(res, _min * (i - j + 1));
            }
        }
        return res;
    }
};

int main() {
    int a[6] = {1,2,3,4,5};
    vector<int> h;
    for (int i = 0; i < 5; i++)
        h.push_back(a[i]);
    Solution s;
    int res = s.largestRectangleArea(h);
    return 0;
}

