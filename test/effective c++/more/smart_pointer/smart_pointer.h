#ifndef SMART_POINTER_H
#define SMART_POINTER_H

using namespace std;

template<class T>
class SmartPtr {
public:
	SmartPtr(T* realPtr = 0);
	SmartPtr(const SmartPtr& rhs);
	~SmartPtr();
	SmartPtr& operator=(const SmartPtr& rhs);
	T* operator->() const;
	T& operator*() const;
private:
	T *pointee;
};

template<class T>
class auto_ptr {
public:
	auto_ptr(T *ptr = 0): pointee(ptr) {}
	~auto_ptr() { delete pointee; }
	auto_ptr(auto_ptr& rhs);
	auto_ptr<T>& operator=(auto_ptr<T>& rhs);
	T& operator*() const;
	T* operator->() const;
private:
	T *pointee;
};

template<class T>
auto_ptr<T>::auto_ptr(auto_ptr<T>& rhs) {
	pointee = rhs.pointee;
	rhs.pointee = 0;
}

template<class T>
auto_ptr<T>::operator=(auto_ptr<T>& rhs) {
	if (*this == rhs)
		return *this;
	delete pointee;
	pointee = rhs.pointee;
	rhs.pointee = 0;
	return *this;
}

template<class T>
auto_ptr<T>::~auto_ptr() {
	delete pointee;
}

template<class T>
T& auto_ptr<T>::operator*() const {
	return *pointee;
}

template<class T>
T* auto_ptr<T>::operator->() const {
	return pointee;
}

#endif