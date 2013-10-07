class Solution {
static const int INF = 65535;
public:
    int threeSumClosest(vector<int> &num, int target) {
        int size = num.size();
        if (size == 0) return 0;
        if (size == 1) return num[0];
        if (size == 2) return num[0] + num[1];
        sort(num.begin(), num.end());
        int res = num[0], min = INF;
        for (int i = 0; i < size; i++) {
            int j = 0, k = size - 1;
            while (j < k) {
                if (j == i) {
                    j++;
                    continue;
                }
                if (k == i) {
                    k--;
                    continue;
                }
                int tmp = num[j] + num[k];
                if (tmp + num[i] == target) return target;
                if (abs(tmp + num[i] - target) < min) {
                    min = abs(tmp + num[i] - target);
                    res = tmp + num[i];
                }
                if (tmp + num[i] > target)
                    k--;
                else j++;
            }
        }
        return res;
    }
};
