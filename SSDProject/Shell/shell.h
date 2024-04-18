#pragma once
#include "SSDAdapter.h"
#include <string>
#include <iostream>

using namespace std;

constexpr int MAX_NUM = 100;
constexpr int LENGTH_OF_INPUT_DATA = 10;

class Shell
{
public:
	Shell();

	bool read(int LBA, bool printout=true);

	bool write(int LBA, string data);

	bool erase(int LBA, int size);

	void help();

	bool fullWrite(string data);

	bool fullRead(bool printout=true);

	void selectSsd(SSDInterface* SsdInterfacePtr);

public://test
	bool testApp1(bool printout = true);

	bool testApp2(bool printout = true);

	bool testWrite10AndCompare(bool printout = true);

	bool testLoopWriteAndReadCompare(bool printout = true);
private:
	bool isAddressValid(int LBA);

	bool isDataValid(string data);

	SSDInterface* SsdDriver;
};