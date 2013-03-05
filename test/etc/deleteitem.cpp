#include <stdio.h>

#define NUM 9
void deleteitem(int s[], const int item, int &n);
void print(int s[], const int n);
int main(void) {
	int n = NUM, s[NUM] = {5, 3, 3, 3, 4, 6, 3, 9, 1};
	deleteitem(s, 3, n);
	print(s, n);
}

void deleteitem(int s[], const int item, int &n) {
	int i, k;
	i = 0; k = 0;
	while (i < n) {
		if (s[i++] == item) {
			k++;
			continue;
		}
		else if (k > 0)
			s[i - k - 1] = s[i - 1];
	}
	n -= k;
}

void print(int s[], const int n) {
	int i;
	for (i = 0; i < n; i++)
		printf("%d%c", s[i], i == n - 1 ? '\n' : ' ');
}