#pragma once
#include "SSDAdapter.h"
#include <string>
#include <iostream>
#include "ShellLogger.h"

using namespace std;

constexpr int MAX_NUM = 100;
constexpr int LENGTH_OF_INPUT_DATA = 10;
constexpr int ERASE_MAX_NUM = 10;

class Shell
{
private:
	static Shell* instance;  // Singleton Pattern
	Shell();

public:
	static Shell* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Shell();
		}
		return instance;
	}

	bool read(int LBA, bool printOut = true);

	bool write(int LBA, string data);

	bool erase(int LBA, int size);

	void help();

	bool fullWrite(string data);

	bool fullRead(bool printOut = true);

	void selectSsd(SSDInterface* SsdInterfacePtr);

public://test
	bool testApp1(bool printOut = true);

	bool testApp2(bool printOut = true);

	bool testWrite10AndCompare(bool printOut = true);

	bool testLoopWriteAndReadCompare(bool printOut = true);
private:
	bool isAddressValid(int LBA);

	bool isDataValid(string data);

	SSDInterface* SsdDriver;
	ShellLogger* shellLogger;
};
