#pragma once
#include <string>
using namespace std;

class SSDInterface {
public:
	virtual bool read(int LBA) = 0;
	virtual bool write(int LBA, string data) = 0;
};