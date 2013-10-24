#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

class Solution {
public:
    int numDistinct(string S, string T) {
        memset(dp, 0, sizeof(dp));
        S = "0" + S;
        T = "0" + T;
        dp[0][0] = dp[1][0] = 1;
        for (int i = 1; i < S.size(); i++) {
            for (int j = 1; j < T.size(); j++) {
                if (S[i] == T[j])
                    dp[1][j] = dp[0][j-1] + dp[0][j];
                else
                    dp[1][j] = dp[0][j];
            }
            for (int j = 0; j < T.size(); j++)
                dp[0][j] = dp[1][j];
        }
        return dp[1][T.size() - 1];
    }
private:
    static const int MAX = 1024;
    int dp[2][MAX];
};

int main() {
    //string S = "aaaa", T = "aa";
    //string S = "rabbbit", T = "rabbit";
    //string S = "abcdacdeced", T = "ace";
    string S = "", T = "aa";
    Solution s;
    int res = s.numDistinct(S, T);
    return 0;
}
