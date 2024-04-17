#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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
		vector<string> buf;
		ifstream file("nand.txt");
		string temp;

		if (file.is_open()) {
			while (getline(file, temp))
			{
				buf.push_back(temp);
			}
			file.close();

			buf[lba] = data;
			writeFileTotal("nand.txt", buf);
		}
		else {
			for (int i = 0; i < 100; i++)
				buf.push_back("0x00000000");

			buf[lba] = data;
			writeFileTotal("nand.txt", buf);
		}
		
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

	void writeFileTotal(string fileName, vector<string> buf)
	{
		string data = "";
		for (int i = 0; i < 100; i++) {
			data = data + buf[i] + "\n";
		}
		writeFile(fileName, data);
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