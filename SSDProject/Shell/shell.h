#pragma once
#include <string>
#include <iostream>
#include "SSDAdapter.h"
#include "ShellLogger.h"
#include "ShellTestBuilder.h"
#include "TestCase.h"

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

	void flush();

	void help();

	bool fullWrite(string data);

	bool fullRead(bool printOut = true);

	void selectSsd(SSDInterface* SsdInterfacePtr);

	bool customTest(string comm, bool printOut = true);

	bool checkValidCommand(string command);

	void showAvaiableTestScenario();
private:
	bool isAddressValid(int LBA);

	bool isDataValid(string data);

	SSDInterface* ssdDriver;
	ShellLogger* shellLogger;
	ShellTestBuilder testBuilder;
};
