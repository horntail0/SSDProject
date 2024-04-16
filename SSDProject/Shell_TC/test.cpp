﻿#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "../Shell/shell.cpp"
#include "../SSD/SSDInterface.cpp"

using namespace std;
using namespace testing;

class MockSSD : public SSDInterface {
public:
	MOCK_METHOD(string, read, (int LBA), (override));
	MOCK_METHOD(void, write, (int LBA, string data), (override));
};

class TestShell : public testing::Test {
public:
	Shell shell;
private:

};

TEST_F(TestShell, TestRead) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, read(0))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	
	string input = shell.read(0);
	string result = "0x12345678";

	EXPECT_EQ(input, result);
}

TEST_F(TestShell, TestWrite) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, write(0, "0xABCD1234"))
		.Times(1);

	shell.write(0, "0xABCD1234");
}

TEST_F(TestShell, TestExit) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	shell.exit();
  SUCCEED();
}

TEST_F(TestShell, TestHelp) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	shell.help();
	SUCCEED();
}