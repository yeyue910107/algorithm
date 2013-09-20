#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int> &num) {
        int size = num.size(), sub1 = -1, sub2;
		if (size == 0)
			return;
        for (int i = size - 1; i > 0; i--) {
            if (num[i-1] < num[i]) {
                sub1 = i - 1;
                break;
            }
        }
        if (sub1 == -1) {
            reverse(num, 0, size-1);
            return;
        }
		sub2 = sub1 + 1;
        for (int i = sub2 + 1; i < size; i++)
            if (num[i] > num[sub1]&& num[i] <= num[sub2])
                sub2 = i;
        swap(num, sub1, sub2);
        reverse(num, sub1+1, size-1);
    }
private:
    void swap(vector<int> &num, const int i, const int j) {
        const int tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
    }
    
    void reverse(vector<int> &num, int i, int j) {
        for (; i < j; i++, j--) {
            swap(num, i, j);
        }
    }
};

int main() {
	vector<int> num;
	int s[9] = {2, 3, 1, 3, 3, 6, 5, 2, 0};
	for (int i = 0; i < 5; i++)
		num.push_back(s[i]);
	Solution so;
	so.nextPermutation(num);
	return 0;
}
