#pragma once
#include "TestCase.h"
class testapp3 : public TestCase
{
public:
	testapp3();
	static testapp3* getInstance();
	bool run(bool printOut) override;
	string getTestName() override;

private:
	string testname;
};