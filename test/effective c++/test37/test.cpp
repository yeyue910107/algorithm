#include <iostream>

using namespace std;

enum ShapeColor { Red, Green, Blue };

class Shape {
public:
	//virtual void draw(ShapeColor color = Red) const = 0;
	void draw(ShapeColor color = Red) const {
		doDraw(color);
	}
private:
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle: public Shape {
//public:
	//virtual void draw(ShapeColor color = Green) const { cout << color << endl; }
private:
	virtual void doDraw(ShapeColor color) const { cout << color << endl; }
};

class Circle: public Shape {
//public:
	//virtual void draw(ShapeColor color) const { cout << color << endl; }
private:
	virtual void doDraw(ShapeColor color) const { cout << color << endl; }
};

int main() {
	Shape* ps;
	Shape* pr = new Rectangle;
	Shape* pc = new Circle;
	Rectangle* ppr = new Rectangle;
	Circle* ppc = new Circle;
	pr->draw();
	pc->draw();
	ppr->draw();
	ppc->draw();
	
}