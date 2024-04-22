#pragma once
#include <string>
#include "TestCase.h"
using namespace std;
constexpr int MAX_TESTCASE_NUM = 10;
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
private:
	TestCase* testlist[MAX_TESTCASE_NUM];
};