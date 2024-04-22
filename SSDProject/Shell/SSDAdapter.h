#pragma once
#include "SSDInterface.h"
#include<iostream>
#include<fstream>

using namespace std;

class SSDAdapter : public SSDInterface
{
public:
	SSDAdapter();
	bool read(int LBA, bool printOut) override;
	bool write(int LBA, string data) override;
	bool erase(int LBA, int size) override;
	void flush() override;
};