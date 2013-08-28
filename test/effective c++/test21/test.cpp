#include <iostream>

using namespace std;

class Rational {
public:
	Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
	~Rational() {}
	void print() { cout << n << "/" << d << endl; }
private:
	int n, d;
	friend const Rational operator* (const Rational& lhs, const Rational& rhs) { return Rational(lhs.n * rhs.n, lhs.d * rhs.d); }
};

int main() {
	Rational a(1, 2), b(3, 5), c = a * b;
	c.print();
	return 0;
}