#include <string>
#include "ShellTestBuilder.h"
#include "testapp1.h"
#include "testapp2.h"

using namespace std;
void ShellTestBuilder::makeTestList()
{
	testapp1* a1 = testapp1::getInstance();
	testapp2* a2 = testapp2::getInstance();
	testlist[0] = reinterpret_cast<TestCase*>(a1);
	testlist[1] = reinterpret_cast<TestCase*>(a2);
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
	return false;
}
