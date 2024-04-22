#include "SSDAdapter.h"


SSDAdapter::SSDAdapter() {}

bool SSDAdapter::read(int LBA, bool printOut)
{
	string cmd = "SSD.exe R " + to_string(LBA);
	int result = system(cmd.c_str());

	string filePath = "result.txt";
	ifstream inputFile(filePath);

	if (inputFile.is_open())
	{
		if (!printOut) return true;

		string line;
		while (getline(inputFile, line))
			cout << line << endl;

		inputFile.close();
		return true;
	}

	return false;
}

bool SSDAdapter::write(int LBA, string data)
{
	string cmd = "SSD.exe W " + to_string(LBA) + " " + data;
	int result = system(cmd.c_str());
	return result == 0 ? true : false;
}

bool SSDAdapter::flush()
{
	string cmd = "SSD.exe F";
	int result = system(cmd.c_str());
	return result == 0 ? true : false;
}

bool SSDAdapter::erase(int LBA, int size)
{
	string cmd = "SSD.exe E " + to_string(LBA) + " " + to_string(size);
	int result = system(cmd.c_str());
	return result == 0 ? true : false;
}