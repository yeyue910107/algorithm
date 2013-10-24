#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        assert(a.size() > 0 && b.size() > 0);
        if (a == "0") return b;
        if (b == "0") return a;
        if (b.size() > a.size()) swap(a, b);
        string res = "", s;
        int carry = 0, tmp = 0, i, j;
        s.resize(1);
        for (i = a.size() - 1, j = b.size() - 1; j >= 0; i--, j--) {
            tmp = (a[i] - '0') + (b[j] - '0') + carry;
            carry = tmp / 2;
            s[0] = (tmp % 2) + '0';
            res = s + res;
        }
        for (; i >= 0; i--) {
            tmp = (a[i] - '0') + carry;
            carry = tmp / 2;
            s[0] = (tmp % 2) + '0';
            res = s + res;
        }
        if (carry > 0) {
            s[0] = carry + '0';
            res = s + res;
        }
        return res;
    }
};

int main() {
    string num1 = "11", num2 = "1";
    Solution s;
    string res = s.addBinary(num1, num2);
    return 0;
}
