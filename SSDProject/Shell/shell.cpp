#include <string>
#include "../SSD/SSDInterface.cpp"

using namespace std;

class Shell {
public:
	Shell() {
		// m = new MockSSD();
	}

	void read(int LBA)
	{
		SsdDriver->read(LBA);
	}

	void write(int LBA, string data)
	{
		SsdDriver->write(LBA, data);
	}

	void exit() {}

	void help() {}

	void fullWrite(string data) {}

	void fullRead() {}

	void selectSsd(SSDInterface* SsdInterfacePtr) {
		SsdDriver = SsdInterfacePtr;
	};

private:
	SSDInterface* SsdDriver;
};