#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Shell/shell.cpp"

class TestShell : public testing::Test {
public:
	Shell s;

private:

};

TEST_F(TestShell, Test1) {
	s.read(0);
	SUCCEED();
}