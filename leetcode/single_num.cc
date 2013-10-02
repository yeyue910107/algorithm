class Solution {
public:
    int singleNumber(int A[], int n) {
        if (n == 1)
            return A[0];
        A[1] ^= A[0];
        
        for (A[0] = 2; A[0] < n; A[0]++) {
            A[1] ^= A[A[0]];
        }
        return A[1];
    }
};
