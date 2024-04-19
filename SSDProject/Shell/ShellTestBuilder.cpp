#include <string>
#include "ShellTestBuilder.h"
#include "testapp1.h"
#include "testapp2.h"
#include "write10andcompare.h"
#include "LoopWriteAndReadCompare.h"

using namespace std;
void ShellTestBuilder::makeTestList()
{
	testapp1* a1 = testapp1::getInstance();
	testapp2* a2 = testapp2::getInstance();
	write10andcompare* w1 = write10andcompare::getInstance();
	LoopWriteAndReadCompare* l1 = LoopWriteAndReadCompare::getInstance();

	testlist[0] = reinterpret_cast<TestCase*>(a1);
	testlist[1] = reinterpret_cast<TestCase*>(a2);
	testlist[2] = reinterpret_cast<TestCase*>(w1);
	testlist[3] = reinterpret_cast<TestCase*>(l1);
}

bool ShellTestBuilder::run(string comm, bool printOut)
{
	if (comm == "testapp1")
	{
		return testlist[0]->run(printOut);
	}
	else if (comm == "testapp2")
	{
		return testlist[1]->run(printOut);
	}
	else if (comm == "write10andcompare")
	{
		return testlist[2]->run(printOut);
	}
	else if (comm == "loopwriteandreadcompare")
	{
		return testlist[3]->run(printOut);
	}
	return false;
}
