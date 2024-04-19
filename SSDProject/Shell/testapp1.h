#pragma once
#include "TestCase.h"
class testapp1 : public TestCase
{
public:
	testapp1();
	static testapp1* getInstance();
	bool run(bool printOut);
};