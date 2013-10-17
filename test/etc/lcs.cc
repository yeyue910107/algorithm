#include <iostream>
#include <string>
using namespace std;

enum {LEN1 = 8, LEN2 = 7};

void print_lcs(const string s1, const string s2, const int flat[][LEN2], const int i, const int j) {
    if (i == 0 || j == 0)
        return;
    if (flat[i][j] == 1) {
        print_lcs(s1, s2, flat, i - 1, j - 1);
        cout << s1.at(i);
    }
    else if (flat[i][j] == 2)
        print_lcs(s1, s2, flat, i - 1, j);
    else
        print_lcs(s1, s2, flat, i, j - 1);
}

int main() {
    string s1 = "0abcbdab", s2 = "0bdcaba";
    int l[LEN1][LEN2] = {0}, flat[LEN1][LEN2] = {0}, i, j, tmp;
    for (i = 1; i < LEN1; i++) {
        for (j = 1; j < LEN2; j++) {
            if (s1.at(i) == s2.at(j)) {
                l[i][j] = l[i - 1][j - 1] + 1;
                flat[i][j] = 1;
            }
            else {
                if (l[i - 1][j] >= l[i][j - 1]) {
                    l[i][j] = l[i - 1][j];
                    flat[i][j] = 2;
                }
                else {
                    l[i][j] = l[i][j - 1];
                    flat[i][j] = 3;
                }
            }
        }
    }
    print_lcs(s1, s2, flat, LEN1 - 1, LEN2 - 1);

    return 0;
}
