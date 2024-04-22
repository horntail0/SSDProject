#include <string>
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

	testlist[Index_testapp1] = reinterpret_cast<TestCase*>(TC_testapp1);
	testlist[Index_testapp2] = reinterpret_cast<TestCase*>(TC_testapp2);
	testlist[Index_write10andcompare] = reinterpret_cast<TestCase*>(TC_W10C);
	testlist[Index_loopWriteAndReadCompare] = reinterpret_cast<TestCase*>(TC_LoopWRC);
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
