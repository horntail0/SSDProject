#include "shell.h"

Shell* Shell::instance = nullptr;

Shell::Shell()
{
	ssdDriver = new SSDAdapter;
	shellLogger = ShellLogger::getInstance();
	testBuilder.makeTestList();
}

bool Shell::read(int LBA, bool printOut)
{
	if (isAddressValid(LBA) == false) return false;
	RECORD_LOG("LBA: " + to_string(LBA));
	return ssdDriver->read(LBA, printOut);
}

bool Shell::write(int LBA, string data)
{
	if (isAddressValid(LBA) == false || isDataValid(data) == false) return false;
	RECORD_LOG("LBA: " + to_string(LBA) + " DATA: " + data);
	return ssdDriver->write(LBA, data);
}

bool Shell::erase(int LBA, int size)
{
	if (size <= 0) return false;
	RECORD_LOG("LBA: " + to_string(LBA) + " SIZE: " + to_string(size));

	while (size > ERASE_MAX_NUM)
	{
		if (isAddressValid(LBA) == false) return false;
		if (ssdDriver->erase(LBA, ERASE_MAX_NUM) == false) return false;
		LBA += ERASE_MAX_NUM;
		size -= ERASE_MAX_NUM;
	}
	return ssdDriver->erase(LBA, size);
}

bool Shell::flush()
{
	RECORD_LOG();
	return ssdDriver->flush();
}

void Shell::help()
{
	RECORD_LOG();
	cout << "Please check the following help message: " << endl
		<< "1. Read data from LBA : read { LBA }" << endl
		<< "2. Write data to LBA : write { LBA } { Data }" << endl
		<< "3. Exit program : exit" << endl
		<< "4. Print help description : help" << endl
		<< "5. Write data to all LBA : fullwrite { Data }" << endl
		<< "6. Read full data from all LBA : fullread" << endl
		<< "7. Erase LBA : erase { LBA } { SIZE }" << endl
		<< "8. Erase ranged LBA : erase_range { Start_LBA } { End_LBA }" << endl
		<< "9. Flush data : flush" << endl;
}

bool Shell::fullWrite(string data)
{
	if (isDataValid(data) == false) return false;
	RECORD_LOG("DATA: " + data);
	for (int i = 0; i < MAX_NUM; i++)
	{
		bool result = ssdDriver->write(i, data);
		if (!result) return false;
	}

	return true;
}

bool Shell::fullRead(bool printOut)
{
	RECORD_LOG();
	for (int i = 0; i < MAX_NUM; i++)
	{
		bool result = ssdDriver->read(i, printOut);
		if (!result) return false;
	}
	return true;
}

void Shell::selectSsd(SSDInterface* SsdInterfacePtr)
{
	ssdDriver = SsdInterfacePtr;
};

bool Shell::customTest(string comm, bool printOut)
{
	RECORD_LOG(comm);
	return testBuilder.run(comm, printOut);
}

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

bool Shell::checkValidCommand(string command)
{
	return testBuilder.checkValidCommand(command);
}

void Shell::showAvaiableTestScenario()
{
	testBuilder.showAvaiableTestScenario();
}