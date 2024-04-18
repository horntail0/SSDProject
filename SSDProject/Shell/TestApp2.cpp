#pragma once
#include "TestScenario.h"
#include "shell.h"

class TestApp2 : public TestScenario
{
public:
	TestApp2(Shell* shell)
	{
		sh = shell;
	}
	bool run(bool printout)
	{
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
			bool result = sh->read(i, printout);
			if (!result) return false;
		}

		return true;
	}
private:
	Shell* sh;
};