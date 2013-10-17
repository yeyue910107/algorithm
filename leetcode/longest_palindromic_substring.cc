#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
static const int MAX = 600;
bool dp[MAX][MAX];
int maxi, maxlen;
public:
    string longestPalindrome(string s) {
        maxlen = 1; maxi = 0;
        memset(dp, false, sizeof(dp));
        for (int i = 0; i < s.size(); i++)
            dp[i][i] = true;
        for (int i = 1; i < s.size(); i++) {
            if (s[i-1] == s[i]) {
                dp[i-1][i] = true;
                maxi = i - 1;
                maxlen = 2;
            }
        }
        for (int k = 3; k <= s.size(); k++) {
            for (int i = 0; i + k - 1 < s.size(); i++) {
                int j = i + k - 1;
                if (s[i] == s[j] && dp[i+1][j-1]) {
                    dp[i][j] = true;
                    maxi = i;
                    maxlen = k;
                }
            }
        }
        
        return s.substr(maxi, maxlen);
    }
};

int main() {
    string s = "abbacd";
    Solution so;
    string res = so.longestPalindrome(s);
    return 0;
}
