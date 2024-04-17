#pragma once
#include "SSDInterface.h"
#include<iostream>
#include<fstream>

using namespace std;

class SSDAdapter : public SSDInterface
{
public:
	SSDAdapter();
	bool read(int LBA) override;
	bool write(int LBA, string data) override;
};