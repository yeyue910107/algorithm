#include<iostream>

using namespace std;

enum { MAX = 500005 };
long long res;

void merge(int s[], int t[], int p, int q, int r) {
	int i = p, j = q, k = p;

	while (i < q && j <= r) {
		if (s[i] <= s[j])
			t[k++] = s[i++];
		else {
			t[k++] = s[j++];
			res += q - i;
		}
	}
	while (i < q) {
		//res += r - q + 1;
		t[k++] = s[i++];
	}
	while (j <= r)
		t[k++] = s[j++];
}

void mpass(int s[], int t[], int m, int n) {
	int i = 0;
	while (i + 2*m <= n) {
		merge(s, t, i, i + m, i + 2*m - 1);
		i += 2*m;
	}
	if (i + m < n) {
		merge(s, t, i, i + m, n - 1);
	}
	else
		for (; i < n; i++)
			t[i] = s[i];
}

void mergesort(int s[], int t[], int n) {
	int i = 1;
	while (i <= n) {
		mpass(s, t, i, n);
		i *= 2;
		if (i <= n)
			mpass(t, s, i, n);
		i *= 2;
	}
}

int main() {
	int n, s[MAX], t[MAX];
	while (true) {
		cin >> n;
		if (n == 0)
			break;
		for (int i = 0; i < n; i++)
			cin >> s[i];
		res = 0;
		mergesort(s, t, n);
		cout << res << endl;
	}
	return 0;
}