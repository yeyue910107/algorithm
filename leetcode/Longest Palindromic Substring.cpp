class Solution {
public:
    string longestPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int flag[MAX][MAX];
        memset(flag, 0, MAX*MAX*(sizeof(int)));
        string t(s);
        reverse(t.begin(), t.end());
        int res = lcs(s, t, flag);
        char *tmp = (char*)malloc(res);
        int i, j, k = res - 1;
        i = j = s.size() - 1;
        while (k >= 0) {
        	if (flag[i][j] == 3) {
        		tmp[k--] = s[i];
        		i--;j--;
        	}
        	else if (flag[i][j] == 2)
        		i--;
        	else if (flag[i][j] == 1)
        		j--;
        	else {
        		i--;j--;
			}
        }
        string output = tmp;
        return output;
    }
private:
	static const int MAX = 256;
    int lcs(string s, string t, int flag[][MAX]) {
    	int dp[MAX][MAX];
    	memset(dp, 0, MAX*MAX*sizeof(int));
    	int slen = s.size(), tlen = t.size();
    	for (int i = 0; i < slen; i++) {
    		for (int j = 0; j < tlen; j++) {
    			if (i == 0 || j == 0) {
    				if (s[i] == t[j]) {
    					dp[i][j] = 1;
    					flag[i][j] = 3;
    				}
    				else
    					flag[i][j] = ((i == 0) ? 1 : 2);
    				continue;
    			}
    			if (s[i] == t[j]) {
    				dp[i][j] = dp[i-1][j-1] + 1;
    				flag[i][j] = 3;
    			}
    			else {
    				if (dp[i][j-1] >= dp[i-1][j] && dp[i][j-1] > dp[i-1][j-1])
    					flag[i][j] = 1;
    				if (dp[i-1][j] >= dp[i][j-1] && dp[i-1][j] > dp[i-1][j-1])
    					flag[i][j] = 2;
    				dp[i][j] = max(dp[i-1][j-1], max(dp[i-1][j], dp[i][j-1]));
    			}
    		}
    	}
    	return dp[slen-1][tlen-1];
    }
    
};
