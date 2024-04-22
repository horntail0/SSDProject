#pragma once
#include <string>
#include "TestCase.h"
using namespace std;

enum TestCaseIndex
{
	Index_testapp1 = 0,
	Index_testapp2,
	Index_write10andcompare,
	Index_loopWriteAndReadCompare
};
class ShellTestBuilder
{
public:
	void makeTestList(void);
	bool run(string comm, bool printOut);
	bool checkValidCommand(string command);
	void showAvaiableTestScenario();

private:
	TestCase* testlist[10];
	int numTestCase_;
};