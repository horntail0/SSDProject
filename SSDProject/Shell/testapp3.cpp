#include "testapp3.h"
#include "shell.h"
static testapp3 app3;
testapp3::testapp3()
{
	testname = "testapp3";
}

testapp3* testapp3::getInstance()
{
	return &app3;
}

bool testapp3::run(bool printOut)
{
	Shell* sh = Shell::getInstance();
	ShellLogger* shellLogger = ShellLogger::getInstance();
	RECORD_LOG();

	string data = "0x12345678";
	for (int i = 0; i < 9; i++)
	{
		if (sh->write(0, data) == false)
		{
			return false;
		}
	}

	return true;
}

string testapp3::getTestName()
{
	return testname;
}


