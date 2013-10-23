#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int search(int A[], int n, int target) {
        int pivot = get_pivot(A, n), offset = n - pivot;
        int low = 0, high = n - 1, mid;
        while (low <= high) {
            mid = (((low + high) >> 1) + (n - offset)) % n;
            if (A[mid] == target) return mid;
            else if (A[mid] < target) low = (mid + offset) % n + 1;
            else high = (mid + offset) % n - 1;
        }
        return -1;
    }
    
    int search2(int A[], int n, int target) {
        int low = 0, high = n - 1, mid;
        while (low < high) {
            mid = low + (high - low) / 2;
            if (A[mid] >= A[low]) {
                if (A[low] <= target && target <= A[mid]) high = mid;
                else low = mid + 1;
            }
            else {
                if (A[mid] <= target && target <= A[high]) low = mid;
                else high = mid - 1;
            }
        }
        if (high >= 0 && high < n && A[high] == target) return high;
        else return -1;
    }

private:
    int get_pivot(int A[], const int n) {
        if (n == 1) return 0;
        if (n == 2) return ((A[0] < A[1]) ? 0 : 1);
        int high = n - 1, low = 0, mid;
        while (low <= high) {
            mid = (low + high) >> 1;
            if (mid > 0 && mid < n - 1 && A[mid] < A[mid - 1] && A[mid] < A[mid + 1]) return mid;
            if (A[mid] < A[low]) high = mid - 1;
            else if (A[mid] > A[high]) low = mid + 1;
            else return low;
        }
        return -1;
    }
};

int main() {
    int A[] = {3, 4, 5, 1, 2}, n = sizeof(A) / sizeof(int);
    Solution s;
    int res = s.search(A, n, 1);
    return 0;
}
