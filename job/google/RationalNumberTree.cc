#include <iostream>
#include <fstream>

using namespace std;

int main() {
	fstream in, out;
	in.open("in.txt", ios::in);
	out.open("out.txt", ios::out);
	int cases, id;
	
	in >> cases;
	for (int i = 1; i <= cases; i++) {
		in >> id;
		unsigned long long p, q, n, m, k, tmp;
		
		if (id == 1) {
			in >> n;
			tmp = n; k = 0;
			while (tmp > 0) {
				tmp >>= 1;
				k++;
			}
			// k is get n's bit num
			k--;
			p = q = 1;
			while (k > 0) {
				if ((n & ((unsigned long long)(1) << (k-1))) == 0) // k'th bit is 0
					q += p;
				else p += q; // k'th bit is 1
				k--;
			}
			out << "Case #" << i << ": " <<  p << " " << q << "\r\n";	
		}
		else {
			k = 0;
			int kk = 0;
			in >> n >> m;
			while (n != 1 || m != 1) {
				if (n > m) {
					k |= ((unsigned long long)(1) << kk); // set (kk+1)'th bit as 1
					n -= m;
				}
				else
					m -= n;
				kk++;
			}
			k |= ((unsigned long long)(1) << kk);
			out << "Case #" << i << ": " <<  k << "\r\n";
		}
	}
	in.close();
	out.close();
	
    return 0;
}
