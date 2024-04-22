#include <string>
#include <iostream>
#include "ShellTestBuilder.h"
#include "testapp1.h"
#include "testapp2.h"
#include "write10andcompare.h"
#include "LoopWriteAndReadCompare.h"

using namespace std;
void ShellTestBuilder::makeTestList()
{
	testapp1* TC_testapp1 = testapp1::getInstance();
	testapp2* TC_testapp2 = testapp2::getInstance();
	write10andcompare* TC_W10C = write10andcompare::getInstance();
	LoopWriteAndReadCompare* TC_LoopWRC = LoopWriteAndReadCompare::getInstance();

	numTestCase_ = 0;

	testlist[Index_testapp1] = reinterpret_cast<TestCase*>(TC_testapp1), numTestCase_++;
	testlist[Index_testapp2] = reinterpret_cast<TestCase*>(TC_testapp2), numTestCase_++;
	testlist[Index_write10andcompare] = reinterpret_cast<TestCase*>(TC_W10C), numTestCase_++;
	testlist[Index_loopWriteAndReadCompare] = reinterpret_cast<TestCase*>(TC_LoopWRC), numTestCase_++;
}

bool ShellTestBuilder::run(string comm, bool printOut)
{
	if (comm == "testapp1")
	{
		return testlist[Index_testapp1]->run(printOut);
	}
	else if (comm == "testapp2")
	{
		return testlist[Index_testapp2]->run(printOut);
	}
	else if (comm == "write10andcompare")
	{
		return testlist[Index_write10andcompare]->run(printOut);
	}
	else if (comm == "loopwriteandreadcompare")
	{
		return testlist[Index_loopWriteAndReadCompare]->run(printOut);
	}
	return false;
}

bool ShellTestBuilder::checkValidCommand(string command)
{
	int numTestCase = 0;
	while (numTestCase <= numTestCase_)
	{
		if (testlist[numTestCase] != nullptr)   // 테스트 시나리오가 존재한다면
		{
			if (command == testlist[numTestCase]->getTestName()) return true;
		}
		numTestCase++;
	}

	return false;  // 모든 루프를 돌아도 테스트 시나리오를 찾지 못했다면 false
}

void ShellTestBuilder::showAvaiableTestScenario()
{
	int numTestCase = 0;
	cout << "Available Test Scenario:" << endl;
	while (numTestCase <= numTestCase_)
	{
		if (testlist[numTestCase] != nullptr)   // 테스트 시나리오가 존재한다면
		{
			cout << testlist[numTestCase]->getTestName() << endl;
		}
		numTestCase++;
	}
}