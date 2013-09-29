class Solution {
public:
    bool canJump(int A[], int n) {
        if (n == 0) return false;
        int flag[25000];
        memset(flag, 0, sizeof(flag));
        int _max = 0;
        for (int i = 0; i < n; i++) {
            if (i > flag[_max])
                return false;
            flag[i] = i + A[i];
            if (flag[_max] < flag[i])
                _max = i;
        }
        return true;
    }
};
