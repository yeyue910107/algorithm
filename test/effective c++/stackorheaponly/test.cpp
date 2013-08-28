#include <iostream>

using namespace std;

class CStackOnly {
public:
	CStackOnly() { cout << "constructor of CStackOnly." << endl; }
	~CStackOnly() { cout << "destructor of CStackOnly." << endl; }
private:
	void* operator new(size_t size) {}
	void operator delete(void *ptr) {}
};

class CHeapOnly {
public:
	CHeapOnly() { cout << "constructor of CHeapOnly." << endl; }
	void destroy() { delete this; }
private:
	~CHeapOnly() {}
};


int main() {
	CHeapOnly *p = new CHeapOnly();
	//CHeapOnly p1;
	p->destroy();
	CStackOnly q;
	//CStackOnly *q1 = new CStackOnly();
}