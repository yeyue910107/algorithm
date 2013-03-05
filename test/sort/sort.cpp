#include "sort.h"
#define MAXNUM 128

using namespace std;

Array::Array(const int *_array, const int &num) {
	if (_array == NULL)
		return;
	int i;
	this->num = num;
	for (i = 0; i < num; i ++)
		this->_array[i] = _array[i];
}

Array::Array(const int *_array, const int &num, Sort &sort_impl) {
	if (_array == NULL)
		return;
	int i;
	this->num = num;
	for (i = 0; i < num; i ++)
		this->_array[i] = _array[i];
	this->sort_impl = &sort_impl;
}

void Array::print_array() const {
	int i;
	for (i = 0; i < num; i++)
		cout << _array[i] << ((i == num - 1) ? "\n" : " ");
}

void SelectSort::sort(int s[], int num) {
	int i, j, min, tmp;
	for (i = 0; i < num - 1;i++) {
		for (j = i + 1, min = i; j < num; j++) {
			if (s[j] < s[min])
				min = j;
		}
		if (min != i) {
			tmp = s[i];
			s[i] = s[min];
			s[min] = tmp;
		}
	}
}

void InsertSort::sort(int s[], int num) {
	int i, j, tmp;
	for (i = 1; i < num; i++) {
		tmp = s[i];
		for (j = i - 1; j >= 0 && tmp < s[j]; j--)
			s[j + 1] = s[j];
		s[j + 1] = tmp;
	}
}

void BubbleSort::sort(int s[], int num) {

}

void QuickSort::sort(int s[], int num) {
	quicksort(s, 0, num - 1);	
}

void QuickSort::quicksort(int s[], int m, int n) {
	int i = m + 1, j = n, k = m, tmp;
	if (m < n) {
		while (true) {
			while (i < n && s[i] < s[k])
				i++;
			while (j > m && s[j] > s[k])
				j--;
			if (i < j) {
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
				i++; j++;
			}
			else
				break;
		}
		tmp = s[k];
		s[k] = s[j];
		s[j] = tmp;
		quicksort(s, m, j - 1);
		quicksort(s, j + 1, n);
	}
}

void HeapSort::sort(int s[], const int num) {
	int i ,tmp;
	for (i = (num - 1) / 2; i >= 0; i--)
		adjust(s, i, num);
	tmp = s[0];
	s[0] = s[num - 1];
	s[num - 1] = tmp;

	for (i = 1; i < num - 1; i++) {
		adjust(s, 0, num - i);
		tmp = s[0];
		s[0] = s[num - i - 1];
		s[num - i - 1] = tmp;
	}
}

void HeapSort::adjust(int s[], const int i, const int num) {
	int j = 2 * i + 1, tmp = s[i];
	while (j < num) {
		if (j + 1 < num && s[j + 1] > s[j])
			j++;
		if (tmp > s[j])
			break;
		s[(j - 1) / 2] = s[j];
		j = j * 2 + 1;
	}
	s[(j - 1) / 2] = tmp;
}

void MergeSort::merge(int x[], int y[], const int s, const int u, const int v) {
	int i = s, j = u + 1, k = s;
	while (i <= u && j <= v) {
		if (x[i] < x[j])
			y[k++] = x[i++];
		else
			y[k++] = x[j++];
	}
	while (i <= u)
		y[k++] = x[i++];
	while (j <= v)
		y[k++] = x[j++];
}

void MergeSort::mpass(int x[], int y[], const int n, const int t) {
	int i = 0, j;
	while (i + 2 * t - 1 < n) {
		merge(x, y, i, i + t - 1, i + 2 * t - 1);
		i += 2 * t;
	}
	if (i + t < n)
		merge(x, y, i, i + t - 1, n - 1);
	else
		for (j = i; j < n; j++)
			y[j] = x[j];
}

void MergeSort::sort(int x[], const int n) {
	int i = 1, flag = 0, y[MAX] = {0};
	while (i < n) {
		mpass(x, y, n, i);
		flag ^= 1;
		i *= 2;
		if (i < n) {
			mpass(y, x, n, i);
			flag ^= 1;
		}
		i *= 2;
	}
	if (flag)
		for (i = 0; i < n; i++)
			x[i] = y[i];
}

int main() {
	int s[10] = {7, 9, 1, 5, 4, 6, 3, 2, 8, 10};
	MergeSort _sort;
	Array a(s, 10, _sort);
	a.print_array();
	a.sort();
	a.print_array();
	return 0;
}