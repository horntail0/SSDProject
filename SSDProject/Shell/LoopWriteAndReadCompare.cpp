#include "LoopWriteAndReadCompare.h"
#include "shell.h"

static LoopWriteAndReadCompare loop1;
LoopWriteAndReadCompare::LoopWriteAndReadCompare()
{
	testname = "loopwriteandreadcompare";
}

LoopWriteAndReadCompare* LoopWriteAndReadCompare::getInstance()
{
	return &loop1;
}

bool LoopWriteAndReadCompare::run(bool printOut)
{
	Shell* sh = Shell::getInstance();
	ShellLogger* shellLogger = ShellLogger::getInstance();
	shellLogger->recordLog(__func__, "");

	string data = "0x12345678";

	bool writeOk, readOk;
	for (int i = 0; i < MAX_NUM; i++)
	{
		writeOk = sh->write(i, data);  // 같은 주소에 10번 쓰기, 읽기 테스트
		readOk = sh->read(i, printOut);
	}

	if (writeOk && readOk) return true;
	else return false;
}

string LoopWriteAndReadCompare::getTestName()
{
	return testname;
}