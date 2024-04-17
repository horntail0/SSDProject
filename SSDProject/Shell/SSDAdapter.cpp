#include "SSDInterface.cpp"

class SSDAdapter : public SSDInterface {
	bool read(int LBA) override {
		// do system call
		return true;
	}

	bool write(int LBA, string data) override {
		// do system call
		return true;
	}
};