#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 20005 };

void adjust(int i, int s[], int n) {
	int tmp = s[i], j = 2*i + 1;
	while (j < n) {
		if (j + 1 < n && s[j + 1] < s[j])
			j++;
		if (tmp <= s[j])
			break;
		s[(j-1) / 2] = s[j];
		j = 2*j + 1;
	}
	s[(j-1) / 2] = tmp;
}

long long get_ans(int s[], int n) {
	if (n == 1)
		return s[0];
	if (n == 2)
		return s[0] + s[1];
	
	int i;
	long long res = 0;
	if (n > 3) {
		for (i = n/2 - 1; i >= 0; i--)
			adjust(i, s, n);
		for (i = n; i > 3; i--) {
			int flag = (s[1] < s[2]) ? 1 : 2;
			s[flag] += s[0];
			res += s[flag];
			s[0] = s[i - 1];
			adjust(flag, s, i - 1);
			adjust(0, s, i - 1);
		}
	}
	int tmp = s[0] + min(s[1], s[2]);
	res += tmp + (tmp + max(s[1], s[2]));
	return res;
}

int main() {
	int n, s[MAX];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	cout << get_ans(s, n) << endl;
	return 0;
}