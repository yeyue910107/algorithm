#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

bool cmp(const Interval i1, const Interval i2) {
	return i1.start < i2.start;
}

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
		int size = intervals.size();
		if (size <= 1)
			return intervals;
		vector<Interval> res;
		sort(intervals.begin(), intervals.end(), cmp);
		int i = 0, j = 0, tmp_start = intervals[0].start, tmp_end = intervals[0].end;
		Interval tmp;
		while (i < size && j < size) {
			if (intervals[i].start <= intervals[j].end)
				i++;
			else {
				if (i == j + 1) {
					Interval tmp(tmp_start, tmp_end);
					tmp_start = intervals[i].start;
					tmp_end = intervals[i].end;
					res.push_back(tmp);
				}
				tmp_end = max(tmp_end, intervals[++j].end);
			}
		}
		while (j < size) {
			tmp_end = max(tmp_end, intervals[j++].end);
		}
		Interval end(tmp_start, tmp_end);
		res.push_back(end);
		return res;
    }
};

int main() {
	Interval i0(1, 4), i1(4, 6), i2(8, 10), i3(15, 18);
	vector<Interval> in;
	in.push_back(i0);
	in.push_back(i1);
	//in.push_back(i2);
	//in.push_back(i3);
	Solution s;
	vector<Interval> res;
	res = s.merge(in);
	return 0;
}
