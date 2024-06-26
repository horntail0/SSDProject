#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string NAND_FILE = "nand.txt";
const string RESULT_FILE = "result.txt";
const string DEFAULT_DATA = "0x00000000";
const int DISK_SIZE = 100;

class IFile
{
public:
	virtual void read(int lba) = 0;
	virtual void read(string data) = 0;
	virtual void write(int lba, string data) = 0;
	virtual void erase(int lba, int size) = 0;
	virtual void writeBufToFile(string, vector<string>) = 0;
	virtual vector<string> readFileToBuf(string) = 0;
	virtual void writeFile(string fileName, string data) = 0;
};

class SSDFile : public IFile
{
public:
	void read(int lba) override
	{
		writeFile(RESULT_FILE, getLbaData(NAND_FILE, lba));
	}

	void read(string data) override
	{
		writeFile(RESULT_FILE, data);
	}

	void write(int lba, string data) override
	{
		vector<string> buf = readFileToBuf(NAND_FILE);
		buf[lba] = data;
		writeBufToFile(NAND_FILE, buf);
	}

	void erase(int lba, int size) override
	{
		vector<string> buf = readFileToBuf(NAND_FILE);
		for (int i = lba; i < lba + size && i < DISK_SIZE; ++i)
		{
			buf[i] = DEFAULT_DATA;
		}
		writeBufToFile(NAND_FILE, buf);
	}

	void writeBufToFile(string fileName, vector<string> buf)
	{
		string data = "";
		for (int i = 0; i < DISK_SIZE; i++) 
		{
			data = data + buf[i] + "\n";
		}
		writeFile(fileName, data);
	}

	vector<string> readFileToBuf(string fileName)
	{
		vector<string> ret;

		ifstream file(fileName);
		string temp;

		if (file.is_open())
		{
			while (getline(file, temp))
			{
				ret.push_back(temp);
			}
			file.close();
		}
		else
		{
			for (int i = 0; i < DISK_SIZE; i++)
				ret.push_back(DEFAULT_DATA);
		}

		return ret;
	}

	void writeFile(string fileName, string data)
	{
		ofstream file(fileName);
		if (file.is_open())
		{
			file << data;
			file.close();
		}
	}

private:
	string getLbaData(string fileName, int targetLine)
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
};

