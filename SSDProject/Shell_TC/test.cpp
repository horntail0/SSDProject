#include <gtest/gtest.h>
#include <gmock/gmock.h>
<<<<<<< HEAD
#include "../Shell/shell.cpp"
=======
#include <string>
#include "../SSD/SSDInterface.cpp"

using namespace std;

class MockSSD : public SSDInterface {
public:
	MOCK_METHOD(string, read, (int LBA), (override));
	MOCK_METHOD(void, write, (int LBA, string data), (override));
};
>>>>>>> 49574dd91d598661781678c94895b075612a3329

class TestShell : public testing::Test {
public:
	Shell s;

private:

};

TEST_F(TestShell, Test1) {
	s.read(0);
	SUCCEED();
}