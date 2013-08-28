#include <iostream>

using namespace std;

class Widget { virtual void foo(); };
class SpecialWidget: public Widget {};

void update(SpecialWidget *psw) {
	SpecialWidget sw;
	const SpecialWidget& csw = sw;
	update(const_cast<SpecialWidget*>(&csw));
	update((SpecialWidget*)&csw);
	Widget* pw = new SpecialWidget;
	update(static_cast<SpecialWidget*>(pw));
	update(dynamic_cast<SpecialWidget*>(pw));
}