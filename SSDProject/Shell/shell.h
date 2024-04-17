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

	bool read(int LBA);

	bool write(int LBA, string data);

	void help();

	bool fullWrite(string data);

	bool fullRead();

	void selectSsd(SSDInterface* SsdInterfacePtr);

	bool testApp1(string data);

	bool testApp2();

private:
	bool isAddressValid(int LBA);

	bool isDataValid(string data);

	SSDInterface* SsdDriver;
};