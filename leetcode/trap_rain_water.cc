class Solution {
public:
    int trap(int A[], int n) {
        if (n <= 2) return 0;
        int hst = 0;
        for (int i = 1; i < n; i++) {
            if (A[i] > A[hst])
                hst = i;
        }
        int res = 0, h = 0;
        for (int i = 0; i < hst; i++) {
            if (A[i] > h)
                h = A[i];
            else
                res += h - A[i];
        }
        h = 0;
        for (int i = n - 1; i > hst; i--) {
            if (A[i] > h)
                h = A[i];
            else
                res += h - A[i];
        }
        return res;
    }
};
