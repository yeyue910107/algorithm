class Solution {
public:
    static const int MAX = 512;
    int minDistance(string word1, string word2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int dp[MAX][MAX];
        int len1 = word1.size(), len2 = word2.size();
        int i, j;
        if (len1 == 0 || len2 == 0)
            return len1+len2;
        for (i = 0; i < len1; i++) {
            if (word1[i] == word2[0]) {
                dp[i][0] = i;
                break;
            }
            dp[i][0] = i+1;
        }
        for (; i < len1; i++)
            dp[i][0] = i;
            
        for (j = 0; j < len2; j++) {
            if (word1[0] == word2[j]) {
                dp[0][j] = j;
                break;
            }
            dp[0][j] = j+1;
        }
        for (; j < len2; j++)
            dp[0][j] = j;
        
        for (int i = 1; i < len1; i++) {
            for (int j = 1; j < len2; j++) {
                int tmp = min(dp[i][j-1], dp[i-1][j])+1;
                if (word1[i] == word2[j]) {
                    dp[i][j] = min(dp[i-1][j-1], tmp);
                }
                else {
                    dp[i][j] = min(dp[i-1][j-1]+1, tmp);
                }
            
            }
        }
        return dp[len1-1][len2-1];
    }
};
