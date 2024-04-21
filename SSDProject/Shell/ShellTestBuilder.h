#pragma once
#include <string>
#include "TestCase.h"
using namespace std;
class ShellTestBuilder
{
public:
	void makeTestList(void);
	bool run(string comm, bool printOut);
private:
	TestCase* testlist[10];
};