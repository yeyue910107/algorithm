#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

enum { MAX = 100005, LEN = 10 };

typedef struct kv {
	char *key, *value;
	kv() { }
	kv(char *key, char *value) : key(key), value(value) { }
}KV;

char *search(const char *s, const KV dic[], const int num) {
	int low = 0, high = num - 1, mid = (low+high) / 2, tmp;
	while (low <= high) {
		tmp = strcmp(s, dic[mid].key);
		if (tmp == 0)
			return dic[mid].value;
		if (tmp < 0)
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low+high) / 2;
	}
	return NULL;
}

int cmp(const void *a, const void *b) {
	return strcmp((*(KV *)a).key, (*(KV *)b).key);
}

int main() {
	KV dic[MAX];
	int num = 0;;
	char buffer[3*LEN], *res, *key, *value;
	bool flag = false;
	while (gets(buffer) != NULL) {
		if (strlen(buffer) == 0) {
			flag = true;
			qsort(dic, num, sizeof(KV), cmp);
			continue;
		}
		if (!flag) {
			key = (char *)malloc(LEN + 1);
			value = (char *)malloc(LEN + 1);
			sscanf(buffer, "%s%s", value, key);
			dic[num++] = KV(key, value);
		}
		else {
			res = search(buffer, dic, num);
			printf("%s\n", (res == NULL) ? "eh" : res);
		}
	}
}