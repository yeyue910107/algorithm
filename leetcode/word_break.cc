#include <iostream>
#include <string>
#include <set>

using namespace std;

class Solution {
static const int MAX = 256;
bool dp[MAX][MAX];
public:
    bool wordBreak(string s, set<string> &dict) {
        int size = s.size(), i, j, k;
		if (size == 0) return true;
		if (dict.size() == 0) return false;
        memset(dp, false, sizeof(dp));
        for (i = 0; i < size; i++) {
            for (j = 0; j+i < size; j++) {
                if (dict.find(s.substr(j, i+1)) != dict.end())
                    dp[j][j+i] = true;
                else {
                    for (k = j; k < j+i; k++) {
                        if (dp[j][k] && dp[k+1][j+i]) {
                            dp[j][j+i] = true;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][size-1];
    }
};

int main() {
	string s = "acaaaaabbbdbcccdcdaadcdccacbcccabbbbcdaaaaaadb";
	string sdic[50] = {"abbcbda","cbdaaa","b","dadaaad","dccbbbc","dccadd","ccbdbc","bbca","bacbcdd","a","bacb","cbc","adc","c","cbdbcad","cdbab","db","abbcdbd","bcb","bbdab","aa","bcadb","bacbcb","ca","dbdabdb","ccd","acbb","bdc","acbccd","d","cccdcda","dcbd","cbccacd","ac","cca","aaddc","dccac","ccdc","bbbbcda","ba","adbcadb","dca","abd","bdbb","ddadbad","badb","ab","aaaaa","acba","abbb"};
	set<string> dict;
	for (int i = 0; i < 50; i++) {
		dict.insert(sdic[i]);
	}
	Solution so;
	bool res = so.wordBreak(s, dict);
	return 0;
}
