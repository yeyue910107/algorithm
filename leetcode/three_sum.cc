#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int>> res;
        int size = num.size();
        if (size < 3)
            return res;
        sort(num.begin(), num.end());
        for (int i = 0; i < size; i++) {
			  if (i > 0 && num[i] == num[i - 1])
				    continue;
            int left = -num[i];
            int j = i + 1, k = size - 1;
            while (j < k) {
                int sum = num[j] + num[k];
                if (sum == left) {
                    vector<int> tmp;
                    tmp.push_back(num[i]);
                    tmp.push_back(num[j]);
                    tmp.push_back(num[k]);
                    res.push_back(tmp);
					          j++; k--;
                }
                else if (sum > left)
                    k--;
                else
                    j++;
            }
        }
        return res;
    }
};

int main() {
	int a[6] = {0, 0, 0, 0, -1, -4};
	vector<int> num;
	vector<vector<int>> res;
	for (int i = 0; i < 4; i++)
		num.push_back(a[i]);
	Solution s;
	res = s.threeSum(num);
	return 0;
}
