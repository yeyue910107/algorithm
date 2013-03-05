#include <iostream>
#include <string.h>
#define MAX_LEN 128
#define MAX_VALUE 65535
using namespace std;

int bracket(int i, int j, char s[], int r[][MAX_LEN], int value[][MAX_LEN]) {
	int ans = MAX_VALUE, k, tmp1, tmp2;
	if (r[i][j] != -1)
		return r[i][j];
	if (i > j)
		return 0;
	if (i == j) {
		r[i][j] = 1;
		return 1;
	}
	if ((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']')) {
		ans = bracket(i + 1, j - 1, s, r, value);
		//if (tmp < ans) {
		//ans = tmp;
		value[i][j] = -1;
		//}
	}
	//if (s[i] == '(' || s[i] == '[')
		//ans = min(bracket(i + 1, j, s, r,value) + 1, ans);
	//if (s[j] == ')' || s[j] == ']')
		//ans = min(bracket(i, j - 1, s, r, value) + 1, ans);
	for (k = i; k < j; k++) {
		tmp1 = bracket(i, k, s, r, value);
		tmp2 = bracket(k + 1, j, s, r, value);
		if (tmp1 + tmp2 < ans) {
			ans = tmp1 + tmp2;
			value[i][j] = k;
		}
		//ans = min(bracket(i, k, s, r, value) + bracket(k + 1, j, s, r, value), ans);
	}
	r[i][j] = ans;
	return ans;
}

void output(int i, int j, char s[], int value[][MAX_LEN]) {
	if (i > j)
		return;
	if (i == j) {
		if (s[i] == '(' || s[i] == ')' )
			cout << "()";
		else if (s[i] == '[' || s[i] == ']')
			cout << "[]";
		return;
	}
	if (value[i][j] == -1) {
		cout << s[i];
		output(i + 1, j - 1, s, value);
		cout << s[j];
	}
	else {
		output(i, value[i][j], s, value);
		output(value[i][j] + 1, j, s, value);
	}
}

void get_ans(char s[]) {
	int i, j, len = strlen(s), dp[MAX_LEN][MAX_LEN], value[MAX_LEN][MAX_LEN] = {0};
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			dp[i][j] = -1;
	bracket(0, len - 1, s, dp, value);
	//cout << bracket(0, len - 1, s, dp, value) << endl;
	output(0, len - 1, s, value);
	cout << endl;
}


int main() {
	char input[MAX_LEN];
	cin >> input;
	get_ans(input);
	return 0;
}