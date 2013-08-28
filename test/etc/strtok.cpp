#include <iostream>

using namespace std;

char* _strtok(char *s, const char *delim) {
	static char *lasts;
	int c, cur;
	char *sp, *tok;

	if (s == NULL && ((s = lasts) == NULL))
		return NULL;
	cout:
	cur = *s++;
	for (sp = const_cast<char *>(delim); (c = *sp++) != 0;)
		if (c == cur)
			goto cout;
	if (cur == 0) {
		lasts = NULL;
		return NULL;
	}
	tok = s - 1;
	for (;;) {
		cur = *s++;
		sp = const_cast<char *>(delim);
		do {
			if ((c = *sp++) == cur) {
				if (cur == 0)
					s = NULL;
				else
					s[-1] = 0;
				lasts = s;
				return tok;
			}
		}
		while (c != 0);
	}
}


char* _strtok_r(char *s, const char *delim, char **last) {
	int c, cur;
	char *sp, *tok;

	if (s == NULL)
		s = *last;
	cout:
	cur = *s++;
	for (sp = const_cast<char *>(delim); (c = *sp++) != 0;)
		if (c == cur)
			goto cout;
	if (cur == 0)
		return NULL;
	tok = s - 1;
	for (;;) {
		cur = *s++;
		sp = const_cast<char *>(delim);
		do {
			if ((c = *sp++) == cur) {
				if (cur == 0) {
					s = NULL;
					*last = strchr(tok, 0);
				}
				else {
					s[-1] = 0;
					*last = s;
				}
				return tok;
			}
		}
		while (c != 0);
	}
}

char* __strtok(char *s, const char* delim) {
	static char* last;
	return _strtok_r(s, delim, &last);
}

int main() {
	char s[29] = "abc de fg,hi jk lmn,o pqr st";
	//const char *delim = " ";
	char *out_token, *in_token, *out, *in;
	out_token = _strtok_r(s, ",", &out);
	while (out_token != NULL) {
		in_token = _strtok_r(out_token, " ", &in);
		while (in_token != NULL) {
			cout << in_token << endl;
			in_token = _strtok_r(NULL, " ", &in);
		}
		out_token = _strtok_r(NULL, ",", &out);
	}
	return 0;
}