#include <iostream>
#include <string>

using namespace std;

class Window {
public:
	Window() {}
	~Window() {}
	Window(const string& name) : name(name) {}
	string get_name() const { return name; }
	virtual void display() const;
private:
	string name;
};

void Window::display() const {
	cout << "Window display." << endl;
}

class WindowWithScrollBars : public Window {
public:
	WindowWithScrollBars(const string& name) : Window(name) { }
	virtual void display() const;
};

void WindowWithScrollBars::display() const {
	cout << "WindowWithScrollBars display." << endl;
}

void printNameAndDisplay(const Window& w) {
	cout << w.get_name() << endl;
	w.display();
}

int main() {
	WindowWithScrollBars wwsb("wwsb");
	printNameAndDisplay(wwsb);
	return 0;
}