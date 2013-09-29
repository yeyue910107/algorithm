class Solution {
public:
    int jump(int A[], int n) {
        int _max = 0, res = 0, k = 0;
        while (_max < n - 1) {
            int tmp = _max;
            for ( ; k <= tmp; k++) {
                _max = max(_max, k + A[k]);
            }
            k = tmp+1;
            res++;
        }
		return res;
    }
};
