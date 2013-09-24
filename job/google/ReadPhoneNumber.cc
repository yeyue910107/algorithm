#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
const int MAX = 128, FORMAT = 256;

int main() {
	fstream in, out;
	in.open("in.txt", ios::in);
	out.open("out.txt", ios::out);
	int cases, formats[MAX], size;
	char num[MAX], format[FORMAT];
	char *buf;
	string rule[10] = {"", "double", "triple", "quadruple", "quintuple", "sextuple", "septuple", "octuple", "nonuple", "decuple"};
	string alpha[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	string res;
	in >> cases;
	for (int i = 1; i <= cases; i++) {
		in >> num >> format;
		int j = 0;
		buf = strtok(format, "-");
		
		while (buf != NULL) {
			formats[j] = atoi(buf);
			buf = strtok(NULL, "-");
			j++;
		}
		size = j;
		int k = 0, form, tmp;
		res = "";
		for(int j = 0; j < size; j++) {
			form = formats[j];
			tmp = 1;
			int len = strlen(num);
			for (int p = 0; p < form; p++) {
				if ((k == len - 1) || (p == form - 1) || num[k] != num[k+1]) {
					if (tmp > 10) {
						for (int q = 0; q < tmp; q++)
							res += " " + alpha[(int)(num[k]-48)];
					}
					else if (tmp > 1)
						res += " " + rule[tmp-1] + " " + alpha[(int)(num[k]-48)];
					else
						res += " " + alpha[(int)(num[k]-48)];
					k++;
					tmp = 1;
					continue;
				}
				k++;
				tmp++;
			}
		}
		out << "Case #" << i << ":" << res << "\r\n";
	}
	in.close();
	out.close();
	
    return 0;
}
