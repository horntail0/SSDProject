#pragma once
#include "TestCase.h"
class LoopWriteAndReadCompare : public TestCase
{
public:
	LoopWriteAndReadCompare();
	static LoopWriteAndReadCompare* getInstance();
	bool run(bool printOut);
	string getTestName() override;

private:
	string testname;
};