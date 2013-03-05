#ifndef _SORT_H
#define _SORT_H
#include <iostream>
#define MAXNUM 128
using namespace std;

class Sort {
public:
	Sort() {}
	virtual ~Sort() {}
	virtual void sort(int *, const int) {}
};

class SelectSort : public Sort {
public:
	void sort(int *, const int);
};

class InsertSort : public Sort {
public:
	void sort(int *, const int);
};

class BubbleSort : public Sort {
public:
	void sort(int *, const int);
};

class QuickSort : public Sort {
public:
	void sort(int *, const int);
private:
	void quicksort(int *, const int, const int);
};

class HeapSort : public Sort {
public:
	void sort(int *, const int);
private:
	void adjust(int *, const int, const int);
};

class MergeSort : public Sort {
public:
	void sort(int *, const int);
private:
	static const int MAX = 128;
	void merge(int *, int *, const int, const int, const int);
	void mpass(int *, int *, const int, const int);
};

class Array {
private:
	int _array[MAXNUM], num;
	Sort *sort_impl;
public:
	Array() {}
	~Array() {}
	void sort() { sort_impl->sort(_array, num); }
	Array(const int *, const int &);
	Array(const int *, const int &num, Sort &);
	void print_array() const;
};

#endif