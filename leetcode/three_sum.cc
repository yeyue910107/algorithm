#include <iostream>
#include <vector>
#include <algorithm>
#include <hash_map>

using namespace std;

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        vector<vector<int>> res;
	hash_map<int, int> _map;
	hash_map<int, int>::iterator it;
        int size = num.size();
        if (size < 3)
            return res;
        sort(num.begin(), num.end());
	for (int i = 0; i < size; i++) {
	    if (_map.find(num[i]) == _map.end())
		_map.insert(pair<int, int>(num[i], 1));
	    else
		_map[num[i]]++;
	    }
        for (int i = 0; i < size; i++) {
	    if (i > 0 && num[i] == num[i - 1])
		continue;
            int left = -num[i];
            /*int j = i + 1, k = size - 1;
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
            }*/
	    for (int j = i + 1; j < size; j++) {
		if (j > i + 1 && num[j] == num[j - 1])
		    continue;
		it = _map.find(left - num[j]);
		if (it != _map.end() && (it->first > num[j] || (it->first == num[j] && it->second > 1))) {
		    if (it->first == 0 && it->second < 3)
			continue;
	  	    vector<int> tmp;
		    tmp.push_back(num[i]);
		    tmp.push_back(num[j]);
		    tmp.push_back(left - num[j]);
		    res.push_back(tmp);
		}
	    }
        }
        return res;
    }
};

int main() {
	int a[6] = {-1, 0, 1, 0, -1, -4};
	vector<int> num;
	vector<vector<int>> res;
	for (int i = 0; i < 4; i++)
	    num.push_back(a[i]);
	Solution s;
	res = s.threeSum(num);
	return 0;
}
