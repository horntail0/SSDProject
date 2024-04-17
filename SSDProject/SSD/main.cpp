#include <iostream>
#include <string>
#include "SSD.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	string cmd = argv[1];
	string index = argv[2];
	int lba = stoi(index);

	SSDFile file;
	SSD ssd;
	ssd.setFile(&file);

	if (cmd == "R") {
		ssd.read(lba);
	}
	if (cmd == "W") {
		string data = argv[3];

		ssd.write(lba, data);
	}

	return 0;
}
