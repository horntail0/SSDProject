#include "testapp1.h"
#include "shell.h"
static testapp1 app1;
testapp1::testapp1()
{
	testname = "testapp1";
}

testapp1* testapp1::getInstance()
{
	return &app1;
}

bool testapp1::run(bool printOut)
{
	Shell* sh = Shell::getInstance();
	ShellLogger* shellLogger = ShellLogger::getInstance();
	RECORD_LOG();

	string data = "0x12345678";
	bool writeOk = sh->fullWrite(data);
	bool readOk = sh->fullRead(printOut);

	if (writeOk && readOk) return true;
	else return false;

}

string testapp1::getTestName()
{
	return testname;
}


