#include <iostream>
#include <assert.h>

using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        assert(divisor != 0);
        if (dividend == 0) return 0;
        bool flag = !((dividend >> 31) ^ (divisor >> 31));
        unsigned int m = abs(dividend), n = abs(divisor); // abs(-2147483648) would overflow with int
        if (m < n) return 0;
        if (n == 1) return (flag ? (int)m : -(int)m);
        int res = 1, i = 1;
        while ((n << 1) > 0 && (n << 1) <= m) {
            n <<= 1;
            i <<= 1;
            res = i;
        }
        if (n == m) return (flag ? i : -i);
        int nn = n;
        while (i > 0) {
            do {
                nn >>= 1;
                i >>= 1;
            } while (i > 0 && n + nn > m);
            res += i;
            n += nn;
        }
        return (flag ? res : -res);
    }
};

int main() {
    Solution s;
    int res = s.divide(-2147483648, 2);
    return 0;
}
