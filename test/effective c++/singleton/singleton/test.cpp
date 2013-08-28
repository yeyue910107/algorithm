#include <iostream>
#include <string>
#include <map>
using namespace std;

class Singleton {
public:
	static void reg(const string&, Singleton*);
	static Singleton* Instance(const string&, const int = 0);
	static map<string, Singleton&>* registry();
	~Singleton() {}
	void setData(const int newData) { data = newData; }
	void print() const { cout << name << " : " << data << endl; }
protected:
	Singleton();
	Singleton(const string& name, const int data = 0) : name(name), data(data) { reg(name, this); }
	static Singleton* lookup(const string& name);
private:
	static Singleton* _instance;
	string name;
	int data;
	static map<string, Singleton&>* _registry;
};

map<string, Singleton&>* Singleton::registry() {
	static map<string, Singleton&> _registry;
	return &_registry;
}

Singleton* Singleton::_instance = 0;
Singleton* Singleton::Instance(const string &name, const int data) {
	/*if (_instance == 0)
		_instance = new Singleton(data);
	return _instance;*/
	//if (_instance == 0) {
		_instance = lookup(name);
		if (!_instance)
			_instance = new Singleton(name, data);
	//}
	return _instance;
}

void Singleton::reg(const string& name, Singleton* s) {
	registry()->insert(make_pair(name, *s));
}

Singleton* Singleton::lookup(const string& name) {
	map<string, Singleton&>::iterator it = registry()->find(name);
	if (it != registry()->end())
		return &(it->second);
	return NULL;
}

int main() {
	Singleton *s1 = Singleton::Instance("s1", 10);
	Singleton *s2 = Singleton::Instance("s2", 20);
	s1->print();
	s2->print();
	delete s1;
	delete s2;
	return 0;
}