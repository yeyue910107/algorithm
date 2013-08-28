#include <iostream>
#include <string>

using namespace std;

class TextBlock {
public:
	TextBlock() {}
	~TextBlock() {}
	TextBlock(const string& s) : text(s) {}
	const char& operator[](std::size_t position) const { return text[position]; }
	char& operator[](std::size_t position) {
		return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]); 
	}
private:
	std::string text;
};

int main() {
	TextBlock tb("hello");
	cout << tb[0] << endl;
	tb[0] = 'x';
	const TextBlock ctb("world");
	cout << ctb[0] << endl;
	return 0;
}