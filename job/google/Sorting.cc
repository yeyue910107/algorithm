#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
const int MAX = 1024;

void swap(int s[], const int i, const int j) {
	const int tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}

void bubble(int s[], const int num, const int start, const bool odd) {
	int p = num - 1, q;
	bool flag = true;
	while (p > 0 && flag) {
		flag = false;
		q = start;
		int gap = 1;
		while (q + gap < num && q <= p) {
			if (q + gap < num && (odd ? ((s[q + gap]&1) != 0) : ((s[q + gap]&1) == 0))) {
				if ((odd ? (s[q] > s[q + gap]) : (s[q] < s[q + gap]))) {
					swap(s, q, q + gap);
					flag = true;
				}
				q += gap;
				gap = 1;
			}
			else gap++;
		}
		p--;
	}
}

int main() {
	fstream in, out;
	in.open("in.txt", ios::in);
	out.open("out.txt", ios::out);
	int cases, num;
	int s[MAX];
	in >> cases;
	for (int i = 1; i <= cases; i++) {
		in >> num;
		int odd = -1, even = -1;
		for (int k = 0; k < num; k++) {
			in >> s[k];
			if (odd == -1 && (s[k]&1) != 0)
				odd = k;
			if (even == -1 && (s[k]&1) == 0)
				even = k;
		}
		bubble(s, num, odd, true);
		bubble(s, num, even, false);
		out << "Case #" << i << ":";
		for (int k = 0; k < num; k++)
			out << " " << s[k];
		out << "\r\n";
	}
	in.close();
	out.close();
	
  return 0;
}
