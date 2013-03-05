#include <iostream>
#include <time.h>
#include "bstree.h"

using namespace std;

#define MAX 255

void create_random_array(int _array[], const int num) {
	int i;
	for (i = 0; i < num; i++)
		_array[i] = rand() % (MAX + 1);
}
int main() {
	BSTree<int> tree;
	int _array[10], num = 10, i;

	srand(time(NULL));
	create_random_array(_array, num);
	for (i = 0; i < num; i++) {
		tree.insert(_array[i]);
		printf("%d%c", _array[i], (i == num - 1) ? '\n' : ' ');
	}
	tree.print();
	//printf("%d\n", tree.depth());
	//tree.remove(_array[0]);
	//tree.print();
	//printf("%d\n", tree.depth());

	return 0;
}