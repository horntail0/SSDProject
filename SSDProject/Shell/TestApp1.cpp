#pragma once
#include "TestScenario.h"
#include "shell.h"

class TestApp1 : public TestScenario
{
public:
	TestApp1(Shell* shell)
	{
		sh = shell;
	}
	bool run(bool printout)
	{
		string data = "0x12345678";
		bool writeOk = sh->fullWrite(data);
		bool readOk = sh->fullRead(printout);

		if (writeOk && readOk) return true;
		else return false;
	}
private:
	Shell* sh;
};