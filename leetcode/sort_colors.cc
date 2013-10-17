#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortColors(int A[], int n) {
        int red = 0, white = 0, blue = 0;
        for (int i = 0; i < n; i++) {
            if (A[i] == 0) red++;
            else if (A[i] == 1) white++;
            else blue++;
        }
        for (int i = 0; i < n; i++) {
            if (i < red) A[i] = 0;
            else if (i < red + white) A[i] = 1;
            else A[i] = 2;
        }
    }

    void sortColors2(int A[], int n) {
        int begin = 0, end = n - 1, cur = 0;
        while (cur <= end) {
            if (A[cur] == 0)
                swap(A[cur++], A[begin++]);
            else if (A[cur] == 1)
                cur++;
            else
                swap(A[cur], A[end--]);
        }
    }
};

int main() {
    int A[] = {0, 1, 1, 2, 0, 2, 1, 1, 0, 0, 2, 2};
    int n = sizeof(A) / sizeof(int);
    Solution s;
    s.sortColors(A, n);
    return 0;
}
