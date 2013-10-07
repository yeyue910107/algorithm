#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        int size = num.size();
        if (size <= 1) return size;
        set<int> _set;
        set<int>::iterator it, cit;
        int res = 0;
        for (int i = 0; i < size; i++) {
            _set.insert(num[i]);
        }
            
        for (int i = 0; i < size; i++) {
            int cur = num[i], cnt = 1;
            cit = _set.find(cur);
            if (cit == _set.end()) continue;
            while (true) {
                it = _set.find(--cur);
                if (it == _set.end())
                    break;
                cnt++;
                _set.erase(it);
            }
            cur = num[i];
            while (true) {
                it = _set.find(++cur);
                if (it == _set.end())
                    break;
                cnt++;
                _set.erase(it);
            }
            _set.erase(cit);
            res = max(res, cnt);
        }
        return res;
    }
};

int main() {
    int a[16] = {-1, 9, -3, -6, 7, -8, 2, 3, -2, 4, 0, 6, 1, -9, 8, 5};
    vector<int> num;
    for (int i = 0; i < 16; i++)
        num.push_back(a[i]);
    Solution s;
    int res = s.longestConsecutive(num);
    return 0;
}
