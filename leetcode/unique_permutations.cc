class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int>> res;
        doPermute(num, 0, res);
        return res;
    }
private:
    void doPermute(vector<int> &num, const int k, vector<vector<int>> &res) {
        int size = num.size();
        if (k == size - 1) {
            res.push_back(num);
            return ;
        }
        
        for (int i = k; i < size; i++) {
            if (isSwap(num, k, i)) {
                swap(num, k, i);
                doPermute(num, k + 1, res);
                swap(num, k, i);
            }
        }
    }
    
    void swap(vector<int> &num, const int i, const int j) {
        const int tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
    }

    bool isSwap(vector<int> &num, const int m, const int n) {
        for (int i = m; i < n; i++)
            if (num[i] == num[n])
                return false;
        return true;
    }
};
