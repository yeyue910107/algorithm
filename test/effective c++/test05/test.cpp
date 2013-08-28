#include <iostream>
#include <string>
using namespace std;

class Empty {
public:
	Empty() {}
	Empty(const Empty& rhs) {}
	~Empty() {}
	Empty& operator =(const Empty& rhs) {}
};

template<typename T>
class NamedObject {
public:
	//NamedObject(const char* name, const T& value) : nameValue(name), objectValue(value) {};
	NamedObject(string& name, const T& value) : nameValue(name), objectValue(value) {}
	NamedObject& operator =(const NamedObject& rhs);
	void print() const { cout << nameValue << ": " << objectValue << endl; }
private:
	string& nameValue;
	const T objectValue;
};

template<typename T>
NamedObject<T>& NamedObject<T>::operator =(const NamedObject& rhs) {
	cout << "copy assignment called." << endl;
	nameValue = rhs.nameValue;
	//objectValue = rhs.objectValue;
	return *this;
}

int main() {
	/*NamedObject<int> no1("smallest prime number", 2);
	NamedObject<int> no2 = no1;
	no1.print();*/
	string newDog("Persephone");
	string oldDog("Satch");
	NamedObject<int> p(newDog, 2);
	NamedObject<int> s(oldDog, 36);
	p.print();
	s.print();
	p = s;
	p.print();
}