#include <string>
using namespace std;

class Shell {
public:
	Shell() {
		// m = new MockSSD();
	}

	void read(int LBA) {}

	void write(int LBA, string data) {}

	void exit() {}

	void help() {}

	void fullWrite(string data) {}

	void fullRead() {}

private:
	// ISSD* m;
};