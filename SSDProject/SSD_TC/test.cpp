#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/File.cpp"
#include "../SSD/SSD.cpp"
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace testing;

const string NORMAL_DATA = "0x12345678";
const string LONG_DATA = "0x123456789";
const string SHORT_DATA = "0x1234567";
const string NOT_HEXA_DATA = "0x1234ABCG";
const string DECIMAL_DATA = "1234567890";

class MockFile : public IFile
{
public:
	MOCK_METHOD(void, read, (int), (override));
	MOCK_METHOD(void, read, (string), (override));
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(void, erase, (int, int), (override));
	MOCK_METHOD(void, writeBufToFile, (string, vector<string>), (override));
	MOCK_METHOD(vector<string>, readFileToBuf, (string), (override));
};

class MockFixture : public testing::Test
{
public:
	void SetUp()
	{
		ssd.setFile(&file);
	}
	MockFile file;
	SSD ssd;
};

class SSDFixture : public testing::Test
{
public:
	void SetUp()
	{
		ssd.setFile(&file);
	}
	void TearDown()
	{
		system(("del " + NAND_FILE).c_str());
		system(("del " + RESULT_FILE).c_str());
	}
	string getData(string fileName, int targetLine)
	{
		int currentLine = 0;
		string data;

		ifstream file(fileName);
		if (file.is_open())
		{
			while (getline(file, data))
			{
				if (currentLine == targetLine)
					break;
				++currentLine;
			}
			file.close();
			return data;
		}
		return "FAIL";
	}
	string getFile(string fileName)
	{
		string ret = "";

		ifstream file(fileName);
		if (file.is_open())
		{
			string data = "";
			while (getline(file, data))
			{
				ret += data;
			}
			file.close();
		}

		return ret;
	}
	SSDFile file;
	SSD ssd;
};

TEST_F(MockFixture, WriteTestInvalidData)
{
	EXPECT_CALL(file, write(_, DECIMAL_DATA))
		.Times(0);
	EXPECT_CALL(file, write(_, SHORT_DATA))
		.Times(0);
	EXPECT_CALL(file, write(_, LONG_DATA))
		.Times(0);
	EXPECT_CALL(file, write(_, NOT_HEXA_DATA))
		.Times(0);

	ssd.write(1, DECIMAL_DATA);
	ssd.write(1, SHORT_DATA);
	ssd.write(1, LONG_DATA);
	ssd.write(1, NOT_HEXA_DATA);
}

TEST_F(MockFixture, WriteTestInvalidLBA)
{
	EXPECT_CALL(file, write(-1, _))
		.Times(0);
	EXPECT_CALL(file, write(100, _))
		.Times(0);

	ssd.write(-1, NORMAL_DATA);
	ssd.write(100, NORMAL_DATA);
}

TEST_F(MockFixture, WriteTestCallOnce)
{
	EXPECT_CALL(file, write(1, NORMAL_DATA))
		.Times(1);

	ssd.write(1, NORMAL_DATA);
}

TEST_F(MockFixture, ReadTestInvalidLBA)
{
	EXPECT_CALL(file, read(-1))
		.Times(0);
	EXPECT_CALL(file, read(100))
		.Times(0);

	ssd.read(-1);
	ssd.read(100);
}

TEST_F(MockFixture, ReadTestCallOnce)
{
	EXPECT_CALL(file, read(1))
		.Times(1);

	ssd.read(1);
}

TEST_F(SSDFixture, WriteTestNormalData)
{
	ssd.write(0, NORMAL_DATA);
	ssd.read(0);
	EXPECT_EQ(getData(NAND_FILE, 0), NORMAL_DATA);

	ssd.write(1, NORMAL_DATA);
	ssd.read(1);
	EXPECT_EQ(getData(NAND_FILE, 1), NORMAL_DATA);

	ssd.write(99, NORMAL_DATA);
	ssd.read(99);
	EXPECT_EQ(getData(NAND_FILE, 99), NORMAL_DATA);
}

TEST_F(SSDFixture, WriteTestInvalidData)
{
	ssd.write(0, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	ssd.write(0, LONG_DATA);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.write(1, SHORT_DATA);
	fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.write(2, NOT_HEXA_DATA);
	fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.write(3, DECIMAL_DATA);
	fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);
}

TEST_F(SSDFixture, WriteTestInvalidLBA)
{
	ssd.write(0, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	ssd.write(-1, NORMAL_DATA);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.write(100, NORMAL_DATA);
	fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);
}

TEST_F(SSDFixture, WriteBufferTestNormalData1)
{
	ssd.write(0, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	ssd.writeBuffer(1, NORMAL_DATA);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.flush();
	fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}

TEST_F(SSDFixture, WriteBufferTestNormalData9)
{
	ssd.write(0, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	for (int i = 1; i <= 9; i++)
		ssd.writeBuffer(i, NORMAL_DATA);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.flush();
	fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}


TEST_F(SSDFixture, WriteBufferTestNormalData10)
{
	ssd.write(0, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	for (int i = 1; i <= 10; i++)
		ssd.writeBuffer(i, NORMAL_DATA);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}

TEST_F(SSDFixture, EraseBufferTestSize1)
{
	for (int i = 0; i <= 10; i++)
		ssd.write(i, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	ssd.eraseBuffer(1,1);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.flush();
	fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}

TEST_F(SSDFixture, EraseBufferTestSize10)
{
	for (int i = 0; i <= 10; i++)
		ssd.write(i, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	ssd.eraseBuffer(1, 10);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);

	ssd.flush();
	fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}

TEST_F(SSDFixture, EraseBufferTest9Times)
{
	for (int i = 0; i <= 10; i++)
		ssd.write(i, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	for (int i=0; i<9; i++)
		ssd.eraseBuffer(i, 1);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_EQ(fileBefore, fileAfter);
}

TEST_F(SSDFixture, EraseBufferTest10Times)
{
	for (int i = 0; i <= 10; i++)
		ssd.write(i, NORMAL_DATA);
	string fileBefore = getFile(NAND_FILE);

	for (int i = 0; i < 10; i++)
		ssd.eraseBuffer(i, 1);
	string fileAfter = getFile(NAND_FILE);
	EXPECT_NE(fileBefore, fileAfter);
}

TEST_F(SSDFixture, ReadTestNormalData)
{
	ssd.write(1, NORMAL_DATA);
	ssd.read(1);
	EXPECT_EQ(getData(RESULT_FILE, 0), NORMAL_DATA);
}

TEST_F(SSDFixture, ReadTestInvalidData)
{
	ssd.write(0, NORMAL_DATA);
	ssd.read(0);

	ssd.write(0, LONG_DATA);
	ssd.read(0);
	EXPECT_NE(getData(RESULT_FILE, 0), LONG_DATA);

	ssd.write(1, SHORT_DATA);
	ssd.read(1);
	EXPECT_NE(getData(RESULT_FILE, 0), SHORT_DATA);

	ssd.write(2, NOT_HEXA_DATA);
	ssd.read(2);
	EXPECT_NE(getData(RESULT_FILE, 0), NOT_HEXA_DATA);

	ssd.write(3, DECIMAL_DATA);
	ssd.read(3);
	EXPECT_NE(getData(RESULT_FILE, 0), DECIMAL_DATA);
}

TEST_F(SSDFixture, ReadTestBeforeWrite)
{
	ssd.read(50);
	EXPECT_EQ(getData(RESULT_FILE, 0), DEFAULT_DATA);
}

TEST_F(SSDFixture, ReadTestInvalidLBA)
{
	ssd.read(-1);
	EXPECT_EQ(getData(RESULT_FILE, 0), "FAIL");
	ssd.read(1000);
	EXPECT_EQ(getData(RESULT_FILE, 0), "FAIL");
}

TEST_F(SSDFixture, EraseTest)
{
	for (int i = 0; i < 10; ++i)
	{
		ssd.write(i, NORMAL_DATA);
	}
	ssd.erase(1,5);

	ssd.read(0);
	EXPECT_EQ(getData(RESULT_FILE, 0), NORMAL_DATA);

	for (int i = 1; i < 6; ++i)
	{
		ssd.read(i);
		EXPECT_EQ(getData(RESULT_FILE, 0), DEFAULT_DATA);
	}
	for (int i = 6; i < 10; ++i)
	{
		ssd.read(i);
		EXPECT_EQ(getData(RESULT_FILE, 0), NORMAL_DATA);
	}
}

TEST_F(SSDFixture, DISABLED_FastWriteTest)
{
	/*ssd.fastWrite(Buffer{ 0, 0, "aaa" });
	EXPECT_EQ(ssd.buf.size(), 1);

	ssd.fastWrite(Buffer{ 1, 1, "bbb" });
	EXPECT_EQ(ssd.buf.size(), 2);

	ssd.fastWrite(Buffer{ 1, 5, "000" });
	EXPECT_EQ(ssd.buf.size(), 2);

	ssd.fastWrite(Buffer{ 2, 2, "ccc" });
	EXPECT_EQ(ssd.buf.size(), 3);

	ssd.read(0);
	ssd.read(1);

	ssd.fastWrite(Buffer{ 7, 7, "ddd" });
	EXPECT_EQ(ssd.buf.size(), 4);

	ssd.fastWrite(Buffer{ 6, 9, "000" });
	EXPECT_EQ(ssd.buf.size(), 4);

	ssd.fastWrite(Buffer{ 4, 5, "000" });
	EXPECT_EQ(ssd.buf.size(), 4);*/
}