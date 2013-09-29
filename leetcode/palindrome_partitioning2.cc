/*class Solution {
public:
    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int dp[128][128];
        bool flag[128][128];
        int len = s.size();
        for (int j = 0; j < len; j++) {
            for (int i = 0; i + j < len; i++) {
                if (j == 0)
                    flag[i][i+j] = true;
                else if (j == 1)
                    flag[i][i+j] = (s[i] == s[i+j]);
                else
                    flag[i][i+j] = ((s[i] == s[i+j]) && flag[i+1][i+j-1]);
            }
        }
        
        for (int j = 0; j < len; j++) {
            for (int i = 0; i + j < len; i++) {
                if (flag[i][i+j])
                    dp[i][i+j] = 0;
                else {
                    dp[i][i+j] = 65535;
                    for (int k = i; k < i+j; k++)
                        dp[i][i+j] = min(dp[i][i+j], dp[i][k]+dp[k+1][i+j]+1);
                }
            }
        }
        return dp[0][len-1];
    }
};*/

class Solution {
public:
    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int dp[2000];
        bool flag[2000][2000];
        int len = s.size();
        for (int j = 0; j < len; j++) {
            for (int i = 0; i + j < len; i++) {
                if (j == 0)
                    flag[i][i+j] = true;
                else if (j == 1)
                    flag[i][i+j] = (s[i] == s[i+j]);
                else
                    flag[i][i+j] = ((s[i] == s[i+j]) && flag[i+1][i+j-1]);
            }
        }
        
        for (int i = 0; i < len; i++) {
            if (flag[0][i])
                dp[i] = 0;
            else {
                dp[i] = 65535;
                for (int k = 0; k < i; k++) {
                    if (flag[k+1][i])
                        dp[i] = min(dp[i],dp[k]+1);
                    else
                        dp[i] = min(dp[i], dp[k]+i-k);
                }
            }
        }
        return dp[len-1];
    }
};
