#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
const int MAX = 64;

bool isvalid(int s[][MAX], const int num) {
    bool flag[MAX];
    int size = num * num;
    for (int i = 0; i < size; i++) {
        memset(flag, false, sizeof(flag));
        for (int j = 0; j < size; j++) {
            if (s[i][j] < 1 || s[i][j] > size || flag[s[i][j]])
                return false;
            flag[s[i][j]] = true;
        }
    }
    for (int i = 0; i < size; i++) {
        memset(flag, false, sizeof(flag));
        for (int j = 0; j < size; j++) {
            if (s[j][i] < 1 || s[j][i] > size || flag[s[j][i]])
                return false;
            flag[s[j][i]] = true;
        }
    }
    
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            memset(flag, false, sizeof(flag));
            for (int k = 0; k < size; k++) {
                int x = i * num + k / num, y = j * num + k % num;
                if (s[x][y] < 1 || s[x][y] > size || flag[s[x][y]])
                    return false;
                flag[s[x][y]] = true;
            }
        }
    }
    return true;
}

int main() {
    fstream in, out;
    in.open("in.txt", ios::in);
    out.open("out.txt", ios::out);
    int cases, num;
    int s[MAX][MAX];
    in >> cases;
    for (int i = 1; i <= cases; i++) {
        in >> num;

        for (int j = 0; j < num * num; j++) {
            for (int k = 0; k < num * num; k++) {
                in >> s[j][k];
            }
        }
        
        out << "Case #" << i << ": " << ((isvalid(s, num)) ? "Yes " : "No") << "\r\n";
    }
    in.close();
    out.close();
    
    return 0;
}
