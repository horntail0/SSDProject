#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/File.cpp"
#include "../SSD/SSD.cpp"

using namespace std;
using namespace testing;

class MockFile : public IFile {
public:
	MOCK_METHOD(void, read, (int), (override));
	MOCK_METHOD(void, write, (int, string), (override));
};

class MockFixture : public testing::Test {
public:
	void SetUp() {
		ssd.setFile(&file);
	}
	MockFile file;
	SSD ssd;
};

class SSDFixture : public testing::Test {
public:
	void SetUp() {
		ssd.setFile(&file);
	}
	SSDFile file;
	SSD ssd;
};

TEST_F(MockFixture, WriteTestInvalidLBA) {
	EXPECT_CALL(file, write(-1, "0x12345678"))
		.Times(0);

	ssd.write(-1, "0x12345678");
}
TEST_F(MockFixture, WriteTestCallOnce) {
	EXPECT_CALL(file, write(1, "0x12345678"))
		.Times(1);

	ssd.write(1, "0x12345678");
}

TEST_F(MockFixture, ReadTest) { //일반적인 read
	EXPECT_CALL(file, read(1))
		.Times(1);

	ssd.read(1);
}

TEST_F(MockFixture, ReadTestInvalidLba) { //0~99 아닌 위치에 read
	EXPECT_CALL(file, read(-1))
		.Times(0);
	EXPECT_CALL(file, read(100))
		.Times(0);

	ssd.read(-1);
	ssd.read(100);
}

TEST_F(SSDFixture, DISABLED_writeFileTest) {
	string data = "0x12345678";
	file.writeFile("test.txt", data);
	EXPECT_EQ(data, file.getData("test.txt", 0));
}

//안써진 곳에 read
