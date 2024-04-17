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
		checkAddressValidity(LBA);
		return SsdDriver->read(LBA);
	}

	bool write(int LBA, string data)
	{
		checkAddressValidity(LBA);
		checkDataValidity(data);
		return SsdDriver->write(LBA, data);
	}

	void exit() {}

	void help()
	{
		cout << "1. Read data from LBA : read {LBA}" << endl
			<< "2. Write data to LBA : write {LBA} {Data}" << endl
			<< "3. Exit program : exit" << endl
			<< "4. Print help description : help" << endl
			<< "5. Write data to all LBA : fullwrite {Data}" << endl
			<< "6. Read full data from all LBA : fullread" << endl;
	}

	bool fullWrite(string data)
	{
		checkDataValidity(data);

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
				cout << SsdDriver->read(i) << endl;
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