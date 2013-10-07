class Solution {
static const int MAX = 512;
int dp[2][MAX];
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int m = triangle.size();
        if (m == 0) return 0;
        int n = triangle[0].size();
        if (n == 0) return 0;
        int res = triangle[0][0];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = res;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0) dp[1][j] = dp[0][j] + triangle[i][j];
                else if (j == i) dp[1][j] = dp[0][j-1] + triangle[i][j];
                else dp[1][j] = min(dp[0][j], dp[0][j-1]) + triangle[i][j];
            }
            res = dp[1][0];
            for (int j = 0; j <= i; j++) {
                res = min(res, dp[1][j]);
                dp[0][j] = dp[1][j];
            }
        }
        return res;
    }
};
