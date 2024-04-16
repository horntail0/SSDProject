#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class IFile 
{
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};

class SSDFile : public IFile 
{
public:
	void read(int lba) override
	{
		writeFile("result.txt", getData("nand.txt", lba));
	}

	void write(int lba, string data) override
	{
	}
private:
	string getData(string fileName, int targetLine) 
	{
		int currentLine = 0;
		string data;

		ifstream file(fileName);
		if (file.is_open())
		{
			while (getline(file, data))
			{
				if (currentLine == targetLine)
					return data;
				++currentLine;
			}
			file.close();
		}

		return "0x00000000";
	}

	void writeFile(string fileName, string data) 
	{
		string line;
		ofstream file(fileName);
		if (file.is_open()) {
			file << data << endl;
			file.close();
		}
	}
};