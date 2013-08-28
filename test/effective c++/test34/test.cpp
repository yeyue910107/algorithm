#include <iostream>
#include <string>

using namespace std;

class Shape {
public:
	virtual void draw() const = 0;
	virtual void error(const string& msg) { cout << "Shape: " << msg << endl; }
	int objectID() const;
};

class Rectangle : public Shape {
public:
	void draw() const { cout << "Rectangle: draw." << endl; }
	void error(const string& msg);
};

void Rectangle::error(const string& msg) {
	Shape::error(msg);
	cout << "Rectangle: " << msg << endl;
}

class Ellipse : public Shape {
};

int main() {
	//Shape* ps = new Shape;
	Shape* ps1 = new Rectangle;
	ps1->draw();
	//ps1->Shape::draw();
	ps1->error("error");
	return 0;
}