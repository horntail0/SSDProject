#include "write10andcompare.h"
#include "shell.h"
using namespace std;
static write10andcompare w10;
write10andcompare::write10andcompare()
{
}

write10andcompare* write10andcompare::getInstance()
{
	return &w10;
}

bool write10andcompare::run(bool printOut)
{
	Shell* sh = Shell::getInstance();
	ShellLogger* shellLogger = ShellLogger::getInstance();
	shellLogger->recordLog(__func__, "");

	string data = "0x12345678";

	bool writeOk, readOk;
	for (int i = 0; i < 10; i++)
	{
		writeOk = sh->write(0, data);  // 같은 주소에 10번 쓰기, 읽기 테스트
		readOk = sh->read(0, printOut);
	}

	if (writeOk && readOk) return true;
	else return false;
	return false;
}
