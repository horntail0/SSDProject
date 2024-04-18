#include "shell.h"

Shell::Shell()
{
	SsdDriver = new SSDAdapter;
}

bool Shell::read(int LBA, bool printout)
{
	if (isAddressValid(LBA) == false) return false;
	shellLogger.recordLog(__func__, "LBA:" + to_string(LBA));
	return SsdDriver->read(LBA, printout);
}

bool Shell::write(int LBA, string data)
{
	if (isAddressValid(LBA) == false || isDataValid(data) == false) return false;
	shellLogger.recordLog(__func__, "LBA:" + to_string(LBA) + " DATA:" + data);
	return SsdDriver->write(LBA, data);
}

bool Shell::erase(int LBA, int size)
{
	bool result;
	if (size <= 0) return false;

	shellLogger.recordLog(__func__, "LBA:" + to_string(LBA) + " SIZE:" + to_string(size));

	while (size > ERASE_MAX_NUM)
	{
		if (isAddressValid(LBA) == false) return false;
		if (SsdDriver->erase(LBA, ERASE_MAX_NUM) == false) return false;
		LBA += ERASE_MAX_NUM;
		size -= ERASE_MAX_NUM;
	}
	return SsdDriver->erase(LBA, size);
}


void Shell::help()
{
	cout << "1. Read data from LBA : read { LBA }" << endl
		<< "2. Write data to LBA : write { LBA } { Data }" << endl
		<< "3. Exit program : exit" << endl
		<< "4. Print help description : help" << endl
		<< "5. Write data to all LBA : fullwrite { Data }" << endl
		<< "6. Read full data from all LBA : fullread" << endl;
}

bool Shell::fullWrite(string data)
{
	if (isDataValid(data) == false) return false;

	for (int i = 0; i < MAX_NUM; i++)
	{
		shellLogger.recordLog(__func__, "LBA: " + to_string(i) + " DATA: " + data);
		bool result = SsdDriver->write(i, data);
		if (!result) return false;
	}

	return true;
}

bool Shell::fullRead(bool printout)
{
	shellLogger.recordLog(__func__, "");

	for (int i = 0; i < MAX_NUM; i++)
	{
		bool result = SsdDriver->read(i, printout);
		if (!result) return false;
	}
	return true;
}

void Shell::selectSsd(SSDInterface* SsdInterfacePtr)
{
	SsdDriver = SsdInterfacePtr;
};

bool Shell::testApp1(bool printout)
{
	shellLogger.recordLog(__func__, "");

	string data = "0x12345678";
	bool writeOk = fullWrite(data);
	bool readOk = fullRead(printout);

	if (writeOk && readOk) return true;
	else return false;
};

bool Shell::testApp2(bool printout)
{
	shellLogger.recordLog(__func__, "");

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
		bool result = SsdDriver->read(i, printout);
		if (!result) return false;
	}

	return true;
};

bool Shell::testWrite10AndCompare(bool printout)
{
	shellLogger.recordLog(__func__, "");

	string data = "0x12345678";

	bool writeOk, readOk;
	for (int i = 0; i < 10; i++)
	{
		writeOk = write(0, data);  // 같은 주소에 10번 쓰기, 읽기 테스트
		readOk = read(0, printout);
	}

	if (writeOk && readOk) return true;
	else return false;
};

bool Shell::testLoopWriteAndReadCompare(bool printout)
{
	shellLogger.recordLog(__func__, "");

	string data = "0x12345678";

	bool writeOk, readOk;
	for (int i = 0; i < MAX_NUM; i++)
	{
		writeOk = write(i, data);  // 같은 주소에 10번 쓰기, 읽기 테스트
		readOk = read(i, printout);
	}

	if (writeOk && readOk) return true;
	else return false;
};


bool Shell::isAddressValid(int LBA)
{
	if (LBA < 0 || LBA >= MAX_NUM)
	{
		cout << "INVALID COMMAND" << endl;
		return false;
	}
	return true;
}

bool Shell::isDataValid(string data)
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
