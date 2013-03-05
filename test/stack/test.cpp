#include <iostream>
#include "stacktest.h"

using namespace std;

int main() {
	Queue<int> q;
	int i = 0, test_array[10] = {2, 6, 1, 9, 10, 5, 4, 7, 3, 8};

	while (i < 10) {
		q.enqueue(test_array[i++]);
	}
	while (!q.is_empty())
		cout << q.dequeue() << endl;
}