#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	string cmd = argv[1];
	string index = argv[2];
	int lba = stoi(index);

	if (cmd == "R") {
		// read
		cout << "read" << endl;
	}
	if (cmd == "W") {
		// write
		cout << "write" << endl;
	}

	return 0;
}
