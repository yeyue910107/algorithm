#include <iostream>

using namespace std;

class Solution {
static const int MAX = 256;
public:
    int lengthOfLongestSubstring(string s) {
        int num[MAX];
        int res = 0, count = 0, i, last = -1;
        memset(num, -1, sizeof(num));
        for (i = 0; i < s.size(); i++) {
            if (num[s[i]] >= 0) {
                last = max(last, num[s[i]]);
            }
			res = max(res, i - last);
			num[s[i]] = i;
        }
        return max(res, i - last - 1);
    }
};

int main() {
	string s = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
	Solution so;
	int res = so.lengthOfLongestSubstring(s);
	return 0;
}
