#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "../Shell/shell.cpp"
#include "../Shell/SSDInterface.cpp"
#include "../SSD/File.cpp"

using namespace std;
using namespace testing;

class MockFile : public IFile
{
public:
	MOCK_METHOD(void, read, (int LBA), (override));
	MOCK_METHOD(void, write, (int LBA, string data), (override));
};

class MockSSDAdapter : public SSDInterface
{
public:
	MockSSDAdapter() : mfile_(nullptr) {}

	void selectMockFile(MockFile* mfile)
	{
		mfile_ = mfile;
	}

	bool read(int LBA) override
	{
		mfile_->read(LBA);
		return true;
	}

	bool write(int LBA, string data) override
	{
		mfile_->write(LBA, data);
		return true;
	}
private:
	MockFile* mfile_;
};

class TestShell : public testing::Test
{
public:
	Shell shell;
	MockFile mfile;
	MockSSDAdapter mssd;
private:
	void SetUp() override
	{
		mssd.selectMockFile(&mfile);
		shell.selectSsd(&mssd);
	}
};

TEST_F(TestShell, TestMockAdapterRead)
{
	EXPECT_CALL(mfile, read(0))
		.Times(1);

	EXPECT_EQ(shell.read(0), true);
}

TEST_F(TestShell, TestMockAdapterWrite)
{
	EXPECT_CALL(mfile, write(0, "0x12345678"))
		.Times(1);

	EXPECT_EQ(shell.write(0, "0x12345678"), true);
}

TEST_F(TestShell, TestMockAdapterExit)
{
	shell.exit();
	SUCCEED();
}

TEST_F(TestShell, TestMockAdapterHelp)
{
	string helpString = "1. Read data from LBA : read { LBA }\n";
	helpString += "2. Write data to LBA : write { LBA } { Data }\n";
	helpString += "3. Exit program : exit\n";
	helpString += "4. Print help description : help\n";
	helpString += "5. Write data to all LBA : fullwrite { Data }\n";
	helpString += "6. Read full data from all LBA : fullread\n";

	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf()); 

	shell.help();
	string result = oss.str();

	std::cout.rdbuf(oldCoutStreamBuf); 

	EXPECT_EQ(result, helpString);
}

TEST_F(TestShell, TestMockAdapterFullRead)
{
	EXPECT_CALL(mfile, read(_))
		.Times(100);

	EXPECT_EQ(shell.fullRead(), true);
}

TEST_F(TestShell, TestMockAdapterFullWrite)
{
	EXPECT_CALL(mfile, write(_, "0x12345678"))
		.Times(100);

	EXPECT_EQ(shell.fullWrite("0x12345678"), true);
}

TEST_F(TestShell, TestMockAdapterApp1) 
{
	EXPECT_CALL(mfile, write(_, "0x12345678"))
		.Times(100);

	EXPECT_CALL(mfile, read(_))
		.Times(100);

	EXPECT_EQ(shell.testApp1("0x12345678"), true);
}

TEST_F(TestShell, TestMockAdapterApp2)
{
	EXPECT_CALL(mfile, write(0, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mfile, write(1, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mfile, write(2, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mfile, write(3, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mfile, write(4, "0xAAAABBBB"))
		.Times(30);
	EXPECT_CALL(mfile, write(5, "0xAAAABBBB"))
		.Times(30);

	EXPECT_CALL(mfile, write(0, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mfile, write(1, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mfile, write(2, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mfile, write(3, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mfile, write(4, "0x12345678"))
		.Times(1);
	EXPECT_CALL(mfile, write(5, "0x12345678"))
		.Times(1);

	EXPECT_CALL(mfile, read(0))
		.Times(1);
	EXPECT_CALL(mfile, read(1))
		.Times(1);
	EXPECT_CALL(mfile, read(2))
		.Times(1);
	EXPECT_CALL(mfile, read(3))
		.Times(1);
	EXPECT_CALL(mfile, read(4))
		.Times(1);
	EXPECT_CALL(mfile, read(5))
		.Times(1);

	EXPECT_EQ(shell.testApp2(), true);
}

TEST_F(TestShell, TestReadAbnormalAddress)
{
	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf()); // 새로운 버퍼로 redirection

	shell.read(100);
	string result = oss.str();

	std::cout.rdbuf(oldCoutStreamBuf); // 복원

	EXPECT_EQ(result, "INVALID COMMAND\n");
}

TEST_F(TestShell, TestWriteAbnormalAddress)
{
	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf()); // 새로운 버퍼로 redirection

	shell.write(100, "0xFFFFFFFF");

	string result = oss.str();
	std::cout.rdbuf(oldCoutStreamBuf); // 복원

	EXPECT_EQ(result, "INVALID COMMAND\n");
}

TEST_F(TestShell, TestWriteAbnormalValue)
{
	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf()); // 새로운 버퍼로 redirection

	shell.write(0, "0xABCDEFGH");
	string result = oss.str();

	std::cout.rdbuf(oldCoutStreamBuf); // 복원

	EXPECT_EQ(result, "INVALID COMMAND\n");
}

TEST_F(TestShell, TestFullWriteAbnormalValue)
{
	std::ostringstream oss;
	auto oldCoutStreamBuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf()); // 새로운 버퍼로 redirection

	shell.fullWrite("0xABCDEFGH");
	string result = oss.str();

	std::cout.rdbuf(oldCoutStreamBuf); // 복원

	EXPECT_EQ(result, "INVALID COMMAND\n");
}
