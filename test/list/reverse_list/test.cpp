#include <iostream>
#include "linkedlist.h"

using namespace std;

int main() {
	Linkedlist<int> list;
	int i = 0, test_array[10] = {2, 6, 1, 9, 10, 5, 4, 7, 3, 8};

	while (i < 10)
		list.add(test_array[i++]);
	list.print();
	list.reverse();
	list.reverse_recursive();
	list.reverse_stack();
	list.print();
	return 0;
}