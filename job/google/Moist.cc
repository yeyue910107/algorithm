#include <iostream>
#include <fstream>
#include <list>
using namespace std;

enum { MAX = 106 };

int main() {
	fstream in, out;
	in.open("in.txt", ios::in);
	out.open("out.txt", ios::out);
	int num, n, res;
	char *buf, tmp[2];
	list<char *> _list;
	list<char *>::iterator it;
	in >> num;
	for (int i = 1; i <= num; i++) {
		in >> n;
		in.getline(tmp, 2);

		res = 0;
		for (int j = 0; j < n; j++) {
			buf = (char *)malloc(MAX);
			in.getline(buf, MAX);
			for (it = _list.begin(); it != _list.end(); it++) {
				if (strcmp(buf, *it) < 0) {
					_list.insert(it, buf);
					res++;
					break;
				}
			}
			if (it == _list.end())
				_list.push_back(buf);
		}
		for (it = _list.begin(); it != _list.end(); it++)
			free(*it);
		_list.clear();
		out << "Case #" << i << ": " << res << "\r\n";
	}
	in.close();
	out.close();
	return 0;
}
