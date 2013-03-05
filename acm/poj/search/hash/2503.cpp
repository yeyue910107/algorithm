/*#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

enum { MAX = 100005, LEN = 10, SLOT = 100 };

typedef struct kv {
	char *key, *value;
	kv() { }
	kv(char *key, char *value) : key(key), value(value) { }
}KV;

KV dic[MAX][SLOT];
int num[MAX] = { 0 };

int elfhash(char *key) {
	unsigned long h = 0;
	while (*key) {
		h = (h << 4) + *key++;
		unsigned long g = h & 0Xf0000000L;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAX;
}

char *search(const char *key, const int pos) {
	for (int i = 0; i < num[pos]; i++) {
		if (strcmp(key, dic[pos][i].key) == 0)
			return dic[pos][i].value;
	}
	return NULL;
}

int main() {
	int pos;
	char buffer[3*LEN], *res, *key, *value;
	bool flag = false;
	while (gets(buffer) != NULL) {
		if (strlen(buffer) == 0) {
			flag = true;
			continue;
		}
		if (!flag) {
			key = (char *)malloc(LEN + 1);
			value = (char *)malloc(LEN + 1);
			sscanf(buffer, "%s%s", value, key);
			pos = elfhash(key);
			dic[pos][num[pos]++] = KV(key, value);
		}
		else {
			pos = elfhash(buffer);
			res = search(buffer, pos);
			printf("%s\n", (res == NULL) ? "eh" : res);
		}
	}
}*/
#include<iostream>
#include<cstdlib>
using namespace std;

enum { MAX = 100005, LEN = 10, ALPHA = 26 };

typedef struct node {
	char c, *value;
	node *next[ALPHA];
	node() { }
	node(char c) : c(c), value(NULL) { memset(next, NULL, sizeof(node*)*ALPHA); }
	node(char c, char *value) : c(c), value(value) { memset(next, NULL, sizeof(node*)*ALPHA); }
}Node;

Node *root;
int num[MAX] = { 0 };

char *search(char *key) {
	Node *node = root;
	while (*key != '\0' && node->next[*key - 'a'] != NULL) {
		node = node->next[*key - 'a'];
		key++;
	}
	if (*key == '\0')
		return node->value;
	return NULL;
}

void create(char *key, char *value) {
	Node *node = root;
	while (*(key + 1) != '\0') {
		if (node->next[*key - 'a'] == NULL)
			node->next[*key - 'a'] = new Node(*key);
		node = node->next[*key - 'a'];
		key++;
	}
	if (node->next[*key - 'a'] == NULL)
		node->next[*key - 'a'] = new Node(*key, value);
	else
		node->next[*key - 'a']->value = value;
}

int main() {
	char buffer[3*LEN], *res, *key, *value;
	bool flag = false;

	root = new Node;
	memset(root->next, NULL, sizeof(Node*)*ALPHA);
	while (gets(buffer) != NULL) {
		if (strlen(buffer) == 0) {
			flag = true;
			continue;
		}
		if (!flag) {
			key = (char *)malloc(LEN + 1);
			value = (char *)malloc(LEN + 1);
			sscanf(buffer, "%s%s", value, key);
			create(key, value);
		}
		else {
			res = search(buffer);
			printf("%s\n", (res == NULL) ? "eh" : res);
		}
	}
	delete root;
	return 0;
}

