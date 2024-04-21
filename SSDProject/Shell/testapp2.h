#pragma once
#include "TestCase.h"
class testapp2 : public TestCase
{
public:
	testapp2();
	static testapp2* getInstance();
	bool run(bool printOut);
};