#include <gtest/gtest.h>
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

TEST_F(TestShell, TestFullRead) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, read(_))
		.Times(100);

	shell.fullRead();
}


TEST_F(TestShell, TestFullWrite) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, write(_, "0x12345678"))
		.Times(100);

	shell.fullWrite("0x12345678");
}

TEST_F(TestShell, TestReadAbnormalAddress) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_THROW(shell.read(100), invalid_argument);
}

TEST_F(TestShell, TestWriteAbnormalAddress) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_THROW(shell.write(100, "0xFFFFFFFF"), invalid_argument);
}

TEST_F(TestShell, TestWriteAbnormalValue) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_THROW(shell.write(0, "0xABCDEFGH"), invalid_argument);
	EXPECT_THROW(shell.write(0, "0xABCDABCDABCD"), invalid_argument);
	EXPECT_THROW(shell.write(0, "0xFFFF"), invalid_argument);
}

TEST_F(TestShell, TestFullWriteAbnormalValue) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_THROW(shell.fullWrite("0xABCDEFGH"), invalid_argument);
	EXPECT_THROW(shell.fullWrite("0xABCDABCDABCD"), invalid_argument);
	EXPECT_THROW(shell.fullWrite("0xFFFF"), invalid_argument);
}

TEST_F(TestShell, TestApp1) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, write(_, "0x12345678"))
		.Times(100);

	EXPECT_CALL(mssd, read(_))
		.Times(100);

	EXPECT_EQ(shell.testApp1("0x12345678"), true);
}

TEST_F(TestShell, TestApp2) {
	MockSSD mssd;
	shell.selectSsd(&mssd);

	EXPECT_CALL(mssd, write(0, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mssd, write(1, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mssd, write(2, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mssd, write(3, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mssd, write(4, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mssd, write(5, "0xAAAABBBB"))
		.Times(30);

	EXPECT_CALL(mssd, write(0, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mssd, write(1, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mssd, write(2, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mssd, write(3, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mssd, write(4, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mssd, write(5, "0x12345678"))
		.Times(1);

	EXPECT_CALL(mssd, read(0))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	EXPECT_CALL(mssd, read(1))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	EXPECT_CALL(mssd, read(2))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	EXPECT_CALL(mssd, read(3))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	EXPECT_CALL(mssd, read(4))
		.Times(1)
		.WillOnce(Return("0x12345678"));
	EXPECT_CALL(mssd, read(5))
		.Times(1)
		.WillOnce(Return("0x12345678"));

	EXPECT_EQ(shell.testApp2(), true);
}
