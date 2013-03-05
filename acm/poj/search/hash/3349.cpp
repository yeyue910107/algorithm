/*#include<iostream>
#include<vector>

using namespace std;

enum { MAX = 100050, LEN = 6, MOD = 14997 };

vector<int> hashtable[MOD];
int arm[MAX][LEN];

int hash_func(int n) {
	return n % MOD;
}

bool cmp(int a[], int b[]){
    int i, j;
    for (i = 0; i < LEN; i++)
        if (a[0] == b[i]){
            for (j = 1; j < LEN; j ++)
                if (a[j] != b[(i+j) % LEN])
                    break;
            if (j == LEN) return true;
            for (j = 1; j < LEN; j++)
                if (a[LEN - j] != b[(i+j) % LEN])
                    break;
            if (j == LEN) return true;
        }
    return false;
}

bool search(vector<int> node, int n) {
	int size = node.size();
	for (int i = 0; i < size; i++) {
		if (cmp(arm[node[i]], arm[n]))
			return true;
	}
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	bool res = false;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < LEN; j++) {
			scanf("%d", &arm[i][j]);
			sum += arm[i][j];
		}
		if (res)
			continue;
		if (search(hashtable[hash_func(sum)], i))
			res = true;
		hashtable[hash_func(sum)].push_back(i);
	}
	
	printf(res ? "Twin snowflakes found.\n" : "No two snowflakes are alike.\n");
	return 0;
}*/

#include<iostream>

using namespace std;

enum { MAX = 100, LEN = 6, MOD = 14997 };
typedef struct node {
	int arm[LEN];
}Node;
Node hashtable[MOD][MAX];
int num[MOD];

int hash_func(int n) {
	return n % MOD;
}

bool cmp(int a[], int b[]){
    int i, j;
    for (i = 0; i < LEN; i++)
        if (a[0] == b[i]){
            for (j = 1; j < LEN; j ++)
                if (a[j] != b[(i+j) % LEN])
                    break;
            if (j == LEN) return true;
            for (j = 1; j < LEN; j++)
                if (a[LEN - j] != b[(i+j) % LEN])
                    break;
            if (j == LEN) return true;
        }
    return false;
}

bool search(Node table[], int size, int arm[]) {
	for (int i = 0; i < size; i++) {
		if (cmp(table[i].arm, arm))
			return true;
	}
	return false;
}

int main() {
	int n, arm[LEN];
	scanf("%d", &n);
	bool res = false;
	for (int i = 0; i < n; i++) {
		int sum = 0, tmp;
		for (int j = 0; j < LEN; j++) {
			scanf("%d", &arm[j]);
			sum += arm[j];
		}
		if (res)
			continue;
		tmp = hash_func(sum);
		if (search(hashtable[tmp], num[tmp], arm))
			res = true;
		for (int j = 0; j < LEN; j++)
			hashtable[tmp][num[tmp]].arm[j] = arm[j];
		num[tmp]++;
	}
	
	printf(res ? "Twin snowflakes found.\n" : "No two snowflakes are alike.\n");
	return 0;
}