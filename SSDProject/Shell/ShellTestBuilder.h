#pragma once
#include <string>
#include "TestCase.h"
using namespace std;
constexpr int MAX_TESTCASE_NUM = 10;

class ShellTestBuilder
{
public:
	void makeTestList(void);
	bool run(string comm, bool printOut);
	bool checkValidCommand(string command);
	void showAvaiableTestScenario();

private:
	TestCase* testlist[MAX_TESTCASE_NUM];
	int numTestCase_;
};