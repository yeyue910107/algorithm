#include <iostream>

using namespace std;

enum { LEN = 128, MAX = 32 };

void reverse(char *start, char *end) {
	if (start == NULL || end == NULL)
		return;
	while (start < end) {
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++; end--;
	}
}

int main() {
	char buf[LEN] = "  AB is not  CD  ";
	reverse(buf, buf+strlen(buf)-1);
	char *p = buf, *q = buf;
	while (*p != 0) {
		while (*q != ' ' && *q != '\0')
			q++;
		reverse(p, q-1);
		while (*q == ' ')
			q++;
		p = q;
	}
	cout << buf << endl;
}

/*int main() {
	char buf[LEN] = "AB is not CD";
	char *stack[MAX], *token, *output = (char *)malloc(strlen(buf) + 1);
	int top = -1;

	token = strtok(buf, " ");
	do {
		stack[++top] = token;
		token = strtok(NULL, " ");
	} while (token != NULL);

	output[0] = 0;
	do {
		output = strcat(output, stack[top--]);
		output = strcat(output, " ");
	}
	while (top > 0);
	output = strcat(output, stack[0]);
	printf("%s\n", output);
	free(output);
}*/

