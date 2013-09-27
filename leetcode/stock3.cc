class Solution {
public:
    int maxProfit(vector<int> &prices) {
        vector<int> profit;
        int _min = 0, tmp = 0, size = prices.size();
        if (size == 0 || size == 1)
            return 0;
        profit.push_back(0);
        for (int i = 1; i < size; i++) {
            if (prices[i] > prices[_min]) {
                tmp = max(tmp, prices[i] - prices[_min]);
            }
            else _min = i;
            profit.push_back(tmp);
        }
        int _max = size - 1;
        int res = profit[_max];
        tmp = 0;
        for (int i = size - 2; i >= 0; i--) {
            if (prices[i] < prices[_max]) {
                tmp = max(tmp, prices[_max] - prices[i]);
            }
            else _max = i;
            res = max(res, tmp + profit[i]);
        }
        return res;
    }
};
