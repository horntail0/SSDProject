#pragma once
#include "TestCase.h"
class write10andcompare : public TestCase
{
public:
	write10andcompare();
	static write10andcompare* getInstance();
	bool run(bool printOut);
};