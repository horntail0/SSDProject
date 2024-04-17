#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";
const string DEFAULT_DATA = "0x00000000";

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
		writeFile(RESULT_FILE, getData(NAND_FILE, lba));
	}

	void write(int lba, string data) override
	{
		vector<string> buf;
		ifstream file(NAND_FILE);
		string temp;

		if (file.is_open())
		{
			while (getline(file, temp))
			{
				buf.push_back(temp);
			}
			file.close();
		}
		else
		{
			for (int i = 0; i < 100; i++)
				buf.push_back(DEFAULT_DATA);
		}
		buf[lba] = data;
		writeFileTotal(NAND_FILE, buf);
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
					break;
				++currentLine;
			}
			file.close();
			return data;
		}

		return DEFAULT_DATA;
	}


	void writeFileTotal(string fileName, vector<string> buf)
	{
		string data = "";
		for (int i = 0; i < 100; i++) 
		{
			data = data + buf[i] + "\n";
		}
		writeFile(fileName, data);
	}

	void writeFile(string fileName, string data)
	{
		ofstream file(fileName);
		if (file.is_open()) 
		{
			file << data << endl;
			file.close();
		}
	}
};