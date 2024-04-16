#pragma once
#include <string>

using namespace std;

class IFile 
{
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, string data) = 0;
};

class SSDFile : public IFile 
{
public:
	void read(int lba) override
	{
	}

	void write(int lba, string data) override
	{
	}
};