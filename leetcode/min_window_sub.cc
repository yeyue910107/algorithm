#include<iostream>

using namespace std;

class Solution {
static const int MAX = 256, INF = 65535;
public:
    string minWindow(string S, string T) {
        int tbit[MAX], sbit[MAX];
        memset(tbit, 0, sizeof(tbit));
		memset(sbit, 0, sizeof(sbit));
        for (int k = 0; k < T.size(); k++)
            tbit[T[k]]++;
		int i = 0, j = 0, start = 0, num = INF;
		while (i < S.size()) {
			sbit[S[i]]++;
			if (contains(tbit, sbit)) {
				if (i - j + 1 < num) {
					start = j; num = i - j + 1;
				}
				while (j <= i) {
					if (contains(tbit, sbit)) {
						if (i - j + 1 < num) {
							start = j; num = i - j + 1;
						}
						sbit[S[j++]]--;
					}
					else {
						sbit[S[j++]]--;
						break;
					}
				}
			}
			i++;
		}
		if (num == INF)
			return "";
		return S.substr(start, num);
    }
private:
	bool contains(int tbit[], int sbit[]) {
		for (int i = 0; i < MAX; i++) {
			if (sbit[i] < tbit[i])
				return false;
		}
		return true;
	}
};

int main() {
	string S = "A", T = "AA";
	Solution s;
	string res = s.minWindow(S, T);
	return 0;
}
