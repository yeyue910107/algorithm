class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        if (A == NULL)
            return 1;
        int i = 0;
        while (i < n) {
            if (A[i] <= n && A[i] > 0 && A[i] != i+1 && A[i] != A[A[i]-1]) {
                swap(A[i], A[A[i]-1]);
            }
            else i++;
        }
       
        for (int i = 0; i < n; i++)
            if (A[i] != i+1)
                return i+1;
        return n+1;
    }
};
