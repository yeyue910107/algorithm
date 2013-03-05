/*#include<iostream>
#include<cstdlib>
using namespace std;

enum { MAX = 500005, LEN = 11, ALPHA = 26 };

typedef struct node {
	char c;
	int id;
	node *next[ALPHA];
	node() { }
	node(char c) : c(c), id(-1) { memset(next, NULL, sizeof(node*)*ALPHA); }
	node(char c, int id) : c(c), id(id) { memset(next, NULL, sizeof(node*)*ALPHA); }
}Node;

Node *root;
int color = 0, ancestor[MAX], _rank[MAX], degree[MAX];

int find_set(int x) {
	if (x != ancestor[x])
		ancestor[x] = find_set(ancestor[x]);
	return ancestor[x];
}

void union_set(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a == b)
		return ;
	if (_rank[a] > _rank[b])
		ancestor[b] = a;
	else {
		if (_rank[a] == _rank[b])
			_rank[b]++;
		ancestor[a] = b;
	}
	//int pa = find_set(a), pb = find_set(b);
	//ancestor[pb] = pa;
}

int create(char *s) {
	Node *node = root;
	while (*(s + 1) != '\0') {
		int i = *s - 'a';
		if (node->next[i] == NULL)
			node->next[i] = new Node(*s);
		node = node->next[i];
		s++;
	}
	if (node->next[*s - 'a'] == NULL)
		node->next[*s - 'a'] = new Node(*s, color++);
	return node->next[*s - 'a']->id;
}

int main() {
	char s1[LEN], s2[LEN];
	bool flag = true;
	int id1, id2;

	root = new Node;
	memset(root->next, NULL, sizeof(Node*)*ALPHA);
	for (int i = 0; i < MAX; i++)
		ancestor[i] = i;
	while (scanf("%s%s", s1, s2) != EOF) {
		id1 = create(s1); degree[id1]++;
		id2 = create(s2); degree[id2]++;
		union_set(id1, id2);
	}
	int tmp = ancestor[0], even = 0, odd = 0;
	for (int i = 0; i < color; i++) {
		if (ancestor[i] != tmp) {
			flag = false;
			break;
		}
		(degree[i] % 2) ? odd++ : even++;
	}
	printf((flag && (even == color || odd == 2)) ? "Possible\n" : "Impossible\n");
	return 0;
}*/

#include<iostream>
#include<cstdlib>
using namespace std;

enum { MAX = 500005, LEN = 11, ALPHA = 26 };

int color = 0, ancestor[MAX], _rank[MAX], degree[MAX], hashtable[MAX];

int find_set(int x) {
	if (x != ancestor[x])
		ancestor[x] = find_set(ancestor[x]);
	return ancestor[x];
}

void union_set(int a, int b) {
	a = find_set(a);
	b = find_set(b);
	if (a == b)
		return ;
	if (_rank[a] > _rank[b])
		ancestor[b] = a;
	else {
		if (_rank[a] == _rank[b])
			_rank[b]++;
		ancestor[a] = b;
	}
}

int Hash(char * str)
{
    int hash = 1;
    while(*str)
        hash = (hash*29 + *str++ - 'a')%9991;
    return hash;
}

int etlhash(char *s) {
	unsigned long h = 0;
	while (*s) {
		h = (h << 4) + *s++;
		unsigned long g = h & 0Xf0000000L;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAX;
}

int main() {
	char s1[LEN], s2[LEN];
	bool flag = true;
	int i, id1, id2;

	for (i = 0; i < MAX; i++)
		ancestor[i] = -1;
	while (scanf("%s%s", s1, s2) != EOF) {
		id1 = Hash(s1); degree[id1]++;
		id2 = Hash(s2); degree[id2]++;
		if (ancestor[id1] == -1)
			ancestor[id1] = id1;
		if (ancestor[id2] == -1)
			ancestor[id2] = id2;
		union_set(id1, id2);
	}
	int tmp, even = 0, odd = 0;
	for (i = 0; i < MAX; i++) {
		if (ancestor[i] != -1) {
			tmp = ancestor[i];
			break;
		}
	}
	for (;i < MAX; i++) {
		if (ancestor[i] != -1) {
			if (ancestor[i] != tmp) {
				flag = false;
				break;
			}
			(degree[i] % 2) ? odd++ : even++;
		}
	}
	printf((flag && (even == color || odd == 2)) ? "Possible\n" : "Impossible\n");
	return 0;
}

