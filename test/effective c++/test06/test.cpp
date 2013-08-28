#include <iostream>

using namespace std;

class Uncopyable {
protected:
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale: private Uncopyable {
};

int main() {
	HomeForSale h1;
	HomeForSale h2;
	HomeForSale h3(h1);
	h1 = h2;
}