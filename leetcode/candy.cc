#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        int res = 0;
        vector<int> candies(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i - 1])
                candies[i] = candies[i - 1] + 1;
            else if (ratings[i] < ratings[i - 1]) {
                int j = i - 1;
                while (j >= 0 && ratings[j] > ratings[j + 1] && candies[j] <= candies[j + 1]) {
                    candies[j] += 1;
                    j--;
                }
            }
        }
        for (int i = 0; i < candies.size(); i++)
            res += candies[i];
        return res;
    }
};

int main() {
    int a[5] = {4,2,3,4,1};
    vector<int> ratings;
    for (int i = 0; i < 5; i++)
        ratings.push_back(a[i]);
    Solution s;
    int res = s.candy(ratings);
    return 0;
}
