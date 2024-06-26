#include "testapp2.h"
#include "shell.h"
static testapp2 app2;
testapp2::testapp2()
{
	testname = "testapp2";
}

testapp2* testapp2::getInstance()
{
	return &app2;
}

bool testapp2::run(bool printOut)
{
	Shell* sh = Shell::getInstance();
	ShellLogger* shellLogger = ShellLogger::getInstance();
	RECORD_LOG();

	string data = "0xAAAABBBB";
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			sh->write(j, data);
		}
	}

	data = "0x12345678";
	for (int i = 0; i <= 5; i++)
	{
		sh->write(i, data);
	}


	for (int i = 0; i <= 5; i++)
	{
		bool result = sh->read(i, printOut);
		if (!result) return false;
	}

	return true;
}

string testapp2::getTestName()
{
	return testname;
}
