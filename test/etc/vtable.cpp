#include <iostream>

using namespace std;

typedef void (*Fun)(void);

class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }
};

class Derive : public Base {
public:
	virtual void f1() { cout << "Derive::f1" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
	virtual void h1() { cout << "Derive::h1" << endl; }
};

class Parent {
protected:
	int iparent;
public:
	Parent() : iparent(10) {}
	virtual void f() { cout << "Parent::f" << endl; }
	virtual void g() { cout << "Parent::g" << endl; }
	virtual void h() { cout << "Parent::h" << endl; }
};

class Child : public Parent {
protected:
	int ichild;
public:
	Child() : ichild(100) {}
	virtual void f() { cout << "Child::f" << endl; }
	virtual void g_child() { cout << "Child::g_child" << endl; }
	virtual void h_child() { cout << "Child::h_child" << endl; }
};

class GrandChild : public Child {
protected:
	int igrandchild;
public:
	GrandChild() : igrandchild(1000) {}
	virtual void f() { cout << "GrandChild::f" << endl; }
	virtual void g_child() { cout << "GrandChild::g_child" << endl; }
	virtual void h_grandchild() { cout << "GrandChild::h_grandchild" << endl; }
};

int main() {
	/*Base b;
	//Base *d = new Derive;
	Derive d;
	//Base d = de;
	cout << (int *)(&b) << endl;
	cout << (int *)*(int *)(&b) << endl;
	Fun pfun = (Fun)*((int *)*(int *)(&b));
	pfun();

	cout << (int *)(&d) << endl;
	cout << (int *)*(int *)(&d) << endl;
	pfun = (Fun)*((int *)*(int *)(&d));
	pfun();
	/*pfun = (Fun)*((int *)*(int *)(&d) + 1);
	pfun();
	pfun = (Fun)*((int *)*(int *)(&d) + 2);
	pfun();
	pfun = (Fun)*((int *)*(int *)(&d) + 3);
	pfun();
	pfun = (Fun)*((int *)*(int *)(&d) + 4);
	pfun();
	pfun = (Fun)*((int *)*(int *)(&d) + 5);
	pfun();*/
	GrandChild gc;
	Fun pfun;
	int **pvtab = (int **)(&gc);
	int i, j;
	cout << (int)*(pvtab+1) << endl;
	for (i = 0; (Fun)*(*pvtab+i) != NULL; i++) {
		pfun = (Fun)*(*pvtab+i);
		pfun();
	}
	
	return 0;
}