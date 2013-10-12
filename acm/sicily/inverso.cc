#include <iostream>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;
const int MAX = 999999999;
const int CLICK[10] = { 0x0000, 0x001B, 0x003F, 0x0036, 0x00DB, 0x01FF, 0x01B6, 0x00D8, 0x01F8, 0x01B0 };

bool contains(int n, const int k) {
    while (n > 0) {
        if (n % 10 == k)
            return true;
        n /= 10;
    }
    return false;
}

int bfs(int n) {
    if (n == 0) return 11;
    queue<int> q, qs;
    q.push(n);
    qs.push(0);
    while (!q.empty()) {
        int cur = q.front(), curs = qs.front();
        q.pop(); qs.pop();    
        if (curs > MAX)
            break;
        if (cur == 0)
            return curs;
        for (int i = 1; i <= 9; i++) {
            if (!contains(curs, i)) {
                q.push(cur ^ CLICK[i]);
                qs.push(curs * 10 + i);
            }
        }
    }
    return 0;
}

int main() {
    int cases, n, res;
    string input;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        cin >> input;
        n = 0;
        for (int k = 0; k < 9; k++) {
            if (input[k] == 'b')
                n |= (1 << k);
        }
        
        res = bfs(n);
        cout << res << endl;
    }
}
