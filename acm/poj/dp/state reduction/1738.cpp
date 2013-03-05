#include<iostream>
using namespace std;
enum { MAX = 50008, INF = 65535 };

typedef struct {
	
}List;

int get_ans(int n, list<int> s) {
	int i, j, k, tmp, sum = 0;
	list<int>::iterator iteri;
	while (n > 3) {
		for (iteri = s.begin(), i = 0; i < n - 1 && iteri;)
		for (i = 0; i < n - 1 && s[i] > s[i + 2]; i++)
			;
		tmp = s[i] + s[i + 1];
		sum += tmp;
		for (j = i - 1; j >= 0 && s[j] < tmp; j--)
			s[j + 1] = s[j];
		s[j + 1] = tmp;
		for (k = i + 1; k < n; k++)
			s[k] = s[k + 1];
		n--;
	}
	if (n == 3)
		return (s[0] < s[2]) ? (s[0] + s[1])*2 + s[2] + sum : (s[2] + s[1])*2 + s[0] + sum;
	if (n == 2)
		return s[0] + s[1];
	if (n == 1)
		return 0;
	return s[0];
}

int main() {
	int n, tmp;
	list<int> stone;
	while (true) {
		cin >> n;
		if (n == 0)
			break;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			stone.push_back(tmp);
		}
		stone.push_back(INF);
		cout << get_ans(n, stone) << endl;
	}
	return 0;
}