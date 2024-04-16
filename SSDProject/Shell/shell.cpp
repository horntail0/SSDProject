#pragma once
#include <string>
#include "../SSD/SSDInterface.cpp"
#include <iostream>

using namespace std;

constexpr int MAX_NUM = 100;
constexpr int LENGTH_OF_INPUT_DATA = 10;

class Shell {
public:
	Shell() {
		// m = new MockSSD();
	}

	string read(int LBA)
	{
		checkAddressValidity(LBA);
		return SsdDriver->read(LBA);
	}

	void write(int LBA, string data)
	{
		checkAddressValidity(LBA);
		checkDataValidity(data);
		SsdDriver->write(LBA, data);
	}

	void exit() {}

	void help() {
		cout << "1. Read data from LBA : read {LBA}" << endl
			<< "2. Write data to LBA : write {LBA} {Data}" << endl
			<< "3. Exit program : exit" << endl
			<< "4. Print help description : help" << endl
			<< "5. Write data to all LBA : fullwrite {Data}" << endl
			<< "6. Read full data from all LBA : fullread" << endl;
	}

	void fullWrite(string data) {
		checkDataValidity(data);
		for (int i = 0; i < MAX_NUM; i++) {
			SsdDriver->write(i, data);
		}
	}

	void fullRead() {
		for (int i = 0; i < MAX_NUM; i++) {
			SsdDriver->read(i);
		}
	}

	void selectSsd(SSDInterface* SsdInterfacePtr) {
		SsdDriver = SsdInterfacePtr;
	};

	void testApp1(string data) {
		fullWrite(data);
		fullRead();
	};

private:
	void checkAddressValidity(int LBA)
	{
		if (LBA < 0 || LBA >= MAX_NUM)
			throw invalid_argument("Invalid Address");
	}

	void checkDataValidity(string data)
	{
		if (data.length() != LENGTH_OF_INPUT_DATA)
			throw invalid_argument("Invalid Data");

		if (data[0] != '0')
			throw invalid_argument("Invalid Data");

		if (data[1] != 'x')
			throw invalid_argument("Invalid Data");

		for (int i = 2; i < LENGTH_OF_INPUT_DATA; i++)
		{
			if ((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'A' && data[i] <= 'F')) continue;
			throw invalid_argument("Invalid Data");
		}
	}

	SSDInterface* SsdDriver;
};