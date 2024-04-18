#pragma once
class TestScenario
{
public:
	TestScenario() {}
	TestScenario(bool printout) {}
	virtual bool run(bool printoout)
	{
		return true;
	}
};