#pragma once
#include <string>
using namespace std;

class SSDInterface
{
public:
	virtual bool read(int LBA, bool printout) = 0;
	virtual bool write(int LBA, string data) = 0;
	virtual bool erase(int LBA, int size) = 0;
};