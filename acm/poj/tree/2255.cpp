#include<iostream>
#include<cstring>

enum { LEN = 26 };
typedef struct node{
	char c;
	struct node *left, *right;
	struct node() {}
	struct node(const char &c) : c(c), left(NULL), right(NULL) {}
}Node;

void getindex(const char *s, const char *t, int *hash) {
	int len = strlen(s), i, j;
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (s[i] == t[j])
				break;
		}
		hash[s[i] - 'A'] = j;
	}
}

/*void buildtree(const char *s, const char *t, int *hash, Node* &root) {
	int len = strlen(s);
	Node* p;
	root->c = s[0];
	root->left = root->right = NULL;
	for (int i = 1; i < len; i++) {
		p = root;
		while (true) {
			if (hash[s[i] - 'A'] < hash[p->c - 'A']) {
				if (p->left == NULL) {
					p->left = new Node(s[i]);
					break;
				}
				else
					p = p->left;
			}
			else {
				if (p->right == NULL) {
					p->right = new Node(s[i]);
					break;
				}
				else
					p = p->right;
			}
		}
	}
}*/

void build(const char c, int *hash, Node* &p) {
	if (p == NULL)
		p = new Node(c);
	else if (hash[c - 'A'] < hash[p->c - 'A'])
		build(c, hash, p->left);
	else
		build(c, hash, p->right);
}

void buildtree(const char *s, const char *t, int *hash, Node* &root) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		build(s[i], hash, root);
	}
}

void post(Node* &root) {
	if (root == NULL)
		return ;
	post(root->left);
	post(root->right);
	printf("%c", root->c);
}

int main() {
	char pre[LEN], in[LEN];
	int hash[LEN];
	Node *root = NULL;

	while (scanf("%s%s", pre, in) != EOF) {
		getindex(pre, in, hash);
		buildtree(pre, in, hash, root);
		post(root);
		printf("\n");
	}

	return 0;
}