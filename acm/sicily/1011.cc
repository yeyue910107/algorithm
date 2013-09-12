#include <iostream>
#include <memory>
#include <cmath>
#include <cstring>
using namespace std;

enum { MAXN = 15, MAXM = 2005 };

long long get_ans(const int n, const int m) {
    unsigned long long dp[MAXN][MAXM], res = 0;
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= m; i++)
        dp[1][i] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = pow(2.0, (double)(i-1)); j <= m; j++) {
            for (int k = j / 2; k >= 1; k--)
                dp[i][j] += dp[i-1][k];
        }
    }
    for (int i = pow(2.0, (double)(n-1)); i <= m; i++)
        res += dp[n][i];
    return res;
}

int main() {
    int case_num, m, n;
    cin >> case_num;
    for (int i = 0; i < case_num; i++) {
        cin >> n >> m;
        cout << "Case " << i+1 << ": n = " << n << ", m = " << m << ", # lists = " << get_ans(n, m) << endl;
    }
    return 0;
}
