#include <iostream>

using namespace std;

class FileSystem {
public:
	FileSystem() {}
	~FileSystem() {}
	FileSystem(const size_t& disks) : disks(disks) {}
	static FileSystem& tfs(size_t disks = 0);
	std::size_t numDisks() const { return disks; }
private:
	std::size_t disks;
};

FileSystem& FileSystem::tfs(size_t disks) {
	static FileSystem fs(disks);
	return fs;
}

class Directory {
public:
	Directory() {}
	Directory(const int& params) : params(params) { disks = FileSystem::tfs(params).numDisks(); }
	~Directory() {}
	Directory& tmpDir();
	void print() { cout << "Directory: " << "num of disks is " << disks << endl; }
private:
	int params, disks;
};

Directory& Directory::tmpDir() {
	static Directory td;
	return td;
}

int main() {
	Directory tmp(10);
	tmp.print();
	return 0;
}