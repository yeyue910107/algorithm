#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s.size() == 0) return 0;
        memset(dp, 0, sizeof(dp));
        s = "0" + s;
        dp[0] = 1;
        dp[1] = ((s[1] == '0') ? 0 : 1);
        for (int i = 2; i < s.size(); i++) {
            string tmp = s.substr(i - 1, 2);
            if (s[i] != '0')
                dp[i] += dp[i - 1];
            if (tmp >= "10" && tmp <= "26")
                dp[i] += dp[i - 2];
        }
        return dp[s.size() - 1];
    }
private:
    static const int MAX = 2100;
    int dp[MAX];
};

int main() {
    string s = "12";
    Solution so;
    int res = so.numDecodings(s);
    return 0;
}
