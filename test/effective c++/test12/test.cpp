#include <iostream>
#include <string>
using namespace std;

void logCall(const string& funcName) {
	cout << funcName << endl;
}

class Customer {
public:
	Customer() {}
	~Customer() {}
	Customer(const string& name) : name(name) {}
	Customer(const Customer&);
	Customer& operator=(const Customer&);
	virtual void print() const { cout << "Customer: " << name << endl; }
protected:
	string name;
};

Customer::Customer(const Customer& rhs) : name(rhs.name) {
	logCall("Customer copy constructor.");
}

Customer& Customer::operator=(const Customer& rhs) {
	logCall("Customer copy assignment operator.");
	name = rhs.name;
	return *this;
}

class PriorityCustomer: public Customer {
public:
	PriorityCustomer() {}
	PriorityCustomer(const PriorityCustomer&);
	PriorityCustomer& operator=(const PriorityCustomer&);
	PriorityCustomer(const string& name, const int priority) : Customer(name), priority(priority) {}
	void print() const { cout << "PriorityCustomer: " << name << ", " << priority << endl; }
private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) : Customer(rhs), priority(rhs.priority) {
	logCall("PriorityCustomer copy constructor.");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator.");
	Customer::operator=(rhs);
	//name = rhs.name;
	priority = rhs.priority;
	return *this;
}

int main() {
	PriorityCustomer pc("pc", 1);
	pc.print();
	PriorityCustomer pc1(pc), pc2;
	pc1.print();
	pc2 = pc;
	pc2.print();
	return 0;
}