#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<int> remain;
        int size = gas.size(), index = -1, i;
        for (i = 0; i < size; i++) {
            if (gas[i] < cost[i])
                index = i;
            remain.push_back(gas[i] - cost[i]);
        }
		if (index == -1) return 0;
        i = (index+size-1)%size;
        int ok = remain[index], res = -1;
        while (i != index % size) {
            ok += remain[i];
            if (ok >= 0) {
				if (remain[i] >= 0) res = i;
				do {
					i = (i+size-1)%size;
					if (remain[i] < 0) break;
					ok += remain[i];
					res = i;
				}
				while (i != index % size);
            }
			else
				i = (i+size-1)%size;
        }
		return (ok >= 0) ? res : -1;
    }
};

int main() {
	vector<int> gas, cost;
	int _gas[50] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
	int _cost[50] = {36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
	for (int i = 0; i < 50; i++) {
		gas.push_back(_gas[i]);
		cost.push_back(_cost[i]);
	}
	Solution s;
	int res = s.canCompleteCircuit(gas, cost);
	return 0;
}
