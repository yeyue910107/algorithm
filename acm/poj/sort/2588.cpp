/*#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 10000 };

int comp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main() {
	int n, s[MAX];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	qsort(s, n, sizeof(int), comp);
	cout << s[n / 2] << endl;
}*/
/*
#include<iostream>
#include<algorithm>

using namespace std;

enum { MAX = 10000 };

void adjust(const int n, int i, int s[]) {
	int tmp = s[i], j = 2*i + 1;
	while (j < n) {
		if (j + 1 < n && s[j + 1] > s[j])
			j++;
		if (tmp >= s[j])
			break;
		s[(j-1) / 2] = s[j];
		j = j*2 + 1;
	}
	s[(j-1) / 2] = tmp;
}

void swap(const int i, const int j, int s[]) {
	int tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}

void heapsort(int n, int s[]) {
	if (n == 1)
		return ;
	int i, m = (n + 1) / 2;
	for (i = (m-1) / 2; i >= 0; i--)
		adjust(m, i, s);
	if (s[m] <= s[0])
		swap(0, m, s);
	for (i = m + 1; i < n; i++) {
		adjust(m, 0, s);
		if (s[i] <= s[0])
			swap(0, i, s);
	}
	adjust(m, 0, s);
}

int main() {
	int n, s[MAX];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	heapsort(n, s);
	cout << s[0] << endl;
}
*/
#include<iostream>

using namespace std;

enum { MAX = 10000, LEN = 1000001 };

int main() {
	int n, s[MAX];
	short count[LEN] = { 0 };
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		count[s[i]]++;
	}
	for (int i = 0, sum = 0; i < LEN; i++) {
		sum += count[i];
		if (sum >= (n+1) / 2) {
			cout << i << endl;
			return 0;
		}
	}
}