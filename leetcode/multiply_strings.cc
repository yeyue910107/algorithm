#include <iostream>
#include <string>
#include <algorithm>
#include <assert.h>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        assert(num1.size() > 0 && num2.size() > 0);
        if (num1 == "0" || num2 == "0") return "0";
        if (num2.size() > num1.size()) swap(num1, num2);
        string res = "0", tmp;
        
        for (int i = num2.size() - 1; i >= 0; i--) {
            tmp = single_mul(num1, num2[i]);
            tmp.append(num2.size() - i - 1, '0');
            res = add(res, tmp);
        }
        return res;
    }
private:
    string single_mul(string num, char c) {
        assert(num.size() > 0 && c >= '0' && c <= '9');
        if (c == '0') return "0";
        if (c == '1') return num;
        string res = "", s;
        int carry = 0, tmp = 0;
        s.resize(1);
        for (int i = num.size() - 1; i >= 0; i--) {
            tmp = (num[i] - '0') * (c - '0') + carry;
            carry = tmp / 10;
            s[0] = (tmp % 10) + '0';
            res = s + res;
        }
        if (carry > 0) {
            s[0] = carry + '0';
            res = s + res;
        }
        return res;
    }

    string add(string num1, string num2) {
        assert(num1.size() > 0 && num2.size() > 0);
        if (num1 == "0") return num2;
        if (num2 == "0") return num1;
        if (num2.size() > num1.size()) swap(num1, num2);
        string res = "", s;
        int carry = 0, tmp = 0, i, j;
        s.resize(1);
        for (i = num1.size() - 1, j = num2.size() - 1; j >= 0; i--, j--) {
            tmp = (num1[i] - '0') + (num2[j] - '0') + carry;
            carry = tmp / 10;
            s[0] = (tmp % 10) + '0';
            res = s + res;
        }
        for (; i >= 0; i--) {
            tmp = (num1[i] - '0') + carry;
            carry = tmp / 10;
            s[0] = (tmp % 10) + '0';
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
    string num1 = "9999999999999999999999", num2 = "999999999999999999999999999999999";
    Solution s;
    string res = s.multiply(num1, num2);
    return 0;
}
