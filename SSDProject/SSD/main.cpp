#include <iostream>
#include <string>
#include "SSD.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 4)
		return 0;

	string cmd = argv[1];
	string index = argv[2];
	int lba = stoi(index);

	SSDFile file;
	SSD ssd;
	ssd.setFile(&file);

	if (cmd == "R")
	{
		ssd.read(lba);
	}
	if (cmd == "W")
	{
		if (argc != 4)
			return 0;

		string data = argv[3];
		//ssd.write(lba, data);
		ssd.writeBuffer(lba, data);
	}
	if (cmd == "E")
	{
		if (argc != 4)
			return 0;

		int size = stoi(string(argv[3]));
		//ssd.erase(lba, size);
		ssd.eraseBuffer(lba, size);
	}
	if (cmd == "F")
	{
		ssd.flush();
	}

	ssd.saveFile();
	return 0;
}
