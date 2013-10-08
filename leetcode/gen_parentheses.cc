class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if (n == 0) return res;
        string s = "";
        dfs(s, 0, 0, n, res);
        return res;
    }
private:
    void dfs(string s, int left, int right, int n, vector<string> &res) {
        if (left == n && right == n) {
            res.push_back(s);
            return;
        }
        if (left < n)
            dfs(s + "(", left + 1, right, n, res);
        if (right < n && right < left)
            dfs(s + ")", left, right + 1, n, res);
    }
};
