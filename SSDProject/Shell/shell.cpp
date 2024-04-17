#pragma once
#include <string>
#include "SSDAdapter.cpp"
#include "SSDInterface.cpp"
#include <iostream>

using namespace std;

constexpr int MAX_NUM = 100;
constexpr int LENGTH_OF_INPUT_DATA = 10;

class Shell
{
public:
	Shell()
	{
		SsdDriver = new SSDAdapter;
	}

	bool read(int LBA)
	{
		if (isAddressValid(LBA) == false) return false;
		return SsdDriver->read(LBA);
	}

	bool write(int LBA, string data)
	{
		if (isAddressValid(LBA) == false || isDataValid(data) == false) return false;
		return SsdDriver->write(LBA, data);
	}

	void exit() {}

	void help()
	{
		cout << "1. Read data from LBA : read { LBA }" << endl
			<< "2. Write data to LBA : write { LBA } { Data }" << endl
			<< "3. Exit program : exit" << endl
			<< "4. Print help description : help" << endl
			<< "5. Write data to all LBA : fullwrite { Data }" << endl
			<< "6. Read full data from all LBA : fullread" << endl;
	}

	bool fullWrite(string data)
	{
		if (isDataValid(data) == false) return false;
		try
		{
			for (int i = 0; i < MAX_NUM; i++)
			{
				SsdDriver->write(i, data);
			}
		}
		catch (exception& e)
		{
			return false;
		}
		return true;
	}

	bool fullRead()
	{
		try
		{
			for (int i = 0; i < MAX_NUM; i++)
			{
				SsdDriver->read(i);
			}
		}
		catch (exception& e)
		{
			return false;
		}
		return true;
	}

	void selectSsd(SSDInterface* SsdInterfacePtr)
	{
		SsdDriver = SsdInterfacePtr;
	};

	bool testApp1(string data)
	{
		bool writeOk, readOk;
		try
		{
			writeOk = fullWrite(data);
			readOk = fullRead();
		}
		catch (exception& e)
		{
			return false;
		}

		if (writeOk && readOk) return true;
		else return false;

	};

	bool testApp2()
	{
		string data = "0xAAAABBBB";
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j <= 5; j++)
			{
				SsdDriver->write(j, data);
			}
		}

		data = "0x12345678";
		for (int i = 0; i <= 5; i++)
		{
			SsdDriver->write(i, data);
		}


		for (int i = 0; i <= 5; i++)
		{
			bool result = SsdDriver->read(i);
			if (!result) return false;
		}

		return true;
	};

private:
	bool isAddressValid(int LBA)
	{
		if (LBA < 0 || LBA >= MAX_NUM)
		{
			cout << "INVALID COMMAND" << endl;
			return false;
		}
		return true;
	}

	bool isDataValid(string data)
	{
		if (data.length() != LENGTH_OF_INPUT_DATA)
		{
			cout << "INVALID COMMAND" << endl;
			return false;
		}

		if (data[0] != '0')
		{
			cout << "INVALID COMMAND" << endl;
			return false;
		}

		if (data[1] != 'x')
		{
			cout << "INVALID COMMAND" << endl;
			return false;
		}

		for (int i = 2; i < LENGTH_OF_INPUT_DATA; i++)
		{
			if ((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'A' && data[i] <= 'F')) continue;
			cout << "INVALID COMMAND" << endl;
			return false;
		}

		return true;
	}

	SSDInterface* SsdDriver;
};