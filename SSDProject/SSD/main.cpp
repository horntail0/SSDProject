#include <iostream>
#include <string>
#include "SSD.cpp"

using namespace std;

bool is_number(const string& s)
{
	auto it = s.begin();
	while (it != s.end() && std::isdigit(*it)) 
		++it;
	return !s.empty() && it == s.end();
}

int main(int argc, char* argv[])
{
	if (argc < 2 || argc > 4) 
		return 0;

	SSDFile file;
	SSD ssd;
	ssd.setFile(&file);
	string cmd = argv[1];
	int lba = 0;

	if (argc >= 3)
	{
		if (is_number(argv[2]) == false)
			return 0;
		lba = stoi(argv[2]);
	}

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
		if (is_number(argv[3]) == false)
			return 0;

		int size  = stoi(argv[3]);
		//ssd.erase(lba, size);
		ssd.eraseBuffer(lba, size);
	}
	if (cmd == "F")
	{
		ssd.flush();
	}

	return 0;
}
