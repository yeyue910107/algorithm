#include <iostream>
#include <algorithm>
using namespace std;
enum { MAX = 1005 };

int asc[MAX], desc[MAX];

void lis(const double s[], const int n) {
	for (int i = 0; i < n; i++)
		asc[i] = desc[i] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (s[i] > s[j])
				asc[i] = max(asc[i], asc[j] + 1);
			if (s[n - i - 1] > s[n - j - 1])
				desc[n - i - 1] = max(desc[n - i - 1], desc[n - j - 1] + 1);
		}
	}
}

int get_ans(const double s[], const int n) {
	int i, j, res = desc[0];
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			res = max(res, asc[i] + desc[j]);
		}
	}
	res = max(res, asc[n - 1]);
	return n - res;
}

int main() {
	int n;
	double soldier[MAX];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> soldier[i];
	lis(soldier, n);
	cout << get_ans(soldier, n) << endl;
	return 0;
}
