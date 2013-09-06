class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        map<int, int> num;
        vector<int> v;
        
        for (int i = 0; i < numbers.size(); i++) {
            num[numbers[i]] = i;
        }
        
        map<int, int>::iterator it;
        for (int i = 0; i < numbers.size(); i++) {
        	it = num.find(target - numbers[i]);
        	if (it != num.end()) {
        		if (i < it->second) {
        			v.push_back(i+1);
        			v.push_back(it->second+1);
        		}
        		else {
        			v.push_back(it->second+1);
        			v.push_back(i+1);
        		}
        		return v;
        	}
        }
        return v;
    }
};
