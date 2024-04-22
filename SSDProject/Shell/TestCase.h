#pragma once
#include <string>
using namespace std;

class TestCase
{
public:
	virtual bool run(bool printOut) = 0;
	virtual string getTestName() = 0;
};