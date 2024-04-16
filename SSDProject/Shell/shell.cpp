#include <string>
#include "../SSD/SSDInterface.cpp"
#include <iostream>

using namespace std;

class Shell {
public:
	Shell() {
		// m = new MockSSD();
	}

	string read(int LBA)
	{
		return SsdDriver->read(LBA);
	}

	void write(int LBA, string data)
	{
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

	void fullWrite(string data) {}

	void fullRead() {}

	void selectSsd(SSDInterface* SsdInterfacePtr) {
		SsdDriver = SsdInterfacePtr;
	};

private:
	SSDInterface* SsdDriver;
};