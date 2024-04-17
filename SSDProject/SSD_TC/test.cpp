#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/File.cpp"
#include "../SSD/SSD.cpp"
#include <fstream>

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
	MOCK_METHOD(void, write, (int, string), (override));
};

class MockFixture : public testing::Test
{
public:
	void SetUp()
	{
		ssd.setFile(&file);
	}
	void TeadDown()
	{
		string buf = "del " + NAND_FILE;
		system(buf.c_str());
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
					return data;
				++currentLine;
			}
			file.close();
		}

		return DEFAULT_DATA;
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

TEST_F(MockFixture, ReadTestCallOnce)
{
	EXPECT_CALL(file, read(1))
		.Times(1);

	ssd.read(1);
}

TEST_F(MockFixture, ReadTestInvalidLba)
{
	EXPECT_CALL(file, read(-1))
		.Times(0);
	EXPECT_CALL(file, read(100))
		.Times(0);

	ssd.read(-1);
	ssd.read(100);
}

TEST_F(SSDFixture, DISABLED_writeFileTest)
{
	string data = "0x12345678";
	//file.writeFile("test.txt", data);
	//EXPECT_EQ(data, file.getData("test.txt", 0));
}

TEST_F(SSDFixture, WriteTestNormalDataInit)
{
	string buf = "del " + NAND_FILE;
	system(buf.c_str());
	ssd.write(0, NORMAL_DATA);
	EXPECT_EQ(getData(NAND_FILE, 0), NORMAL_DATA);
}

TEST_F(SSDFixture, WriteTestNormalData)
{
	ssd.write(0, NORMAL_DATA);
	EXPECT_EQ(getData(NAND_FILE, 0), NORMAL_DATA);
}

TEST_F(SSDFixture, WriteTestInvalidData)
{
	ssd.write(0, LONG_DATA);
	EXPECT_NE(getData(NAND_FILE, 0), LONG_DATA);
	ssd.write(1, SHORT_DATA);
	EXPECT_NE(getData(NAND_FILE, 1), SHORT_DATA);
	ssd.write(2, NOT_HEXA_DATA);
	EXPECT_NE(getData(NAND_FILE, 2), NOT_HEXA_DATA);
	ssd.write(3, DECIMAL_DATA);
	EXPECT_NE(getData(NAND_FILE, 3), DECIMAL_DATA);
}

TEST_F(SSDFixture, ReadTestFileNormal)
{
	string data = "0x12345678";
	ssd.write(1, data);
	ssd.read(1);

	string read = getData("result.txt", 1);

	EXPECT_EQ(read, data);
}
