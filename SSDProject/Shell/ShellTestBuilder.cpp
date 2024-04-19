#include "ShellTestBuilder.h"
#include "testapp1.h"
void ShellTestBuilder::run(TestCase* (*testlist)[10])
{
	testapp1* a1 = testapp1::getInstance();

	(*testlist)[0] = reinterpret_cast<TestCase*>(a1);
	
}
