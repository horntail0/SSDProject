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

TEST(SSDTest, WriteTest) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SSDTest, ReadTest) { //일반적인 read
	MockFile file;
	EXPECT_CALL(file, read(1)).Times(1);
	
	SSD ssd;
	ssd.setFile(&file);
	ssd.read(1);
}

TEST(SSDTest, ReadTestInvalidLba) { //0~99 아닌 위치에 read
	MockFile file;
	EXPECT_CALL(file, read(-1)).Times(0);
	EXPECT_CALL(file, read(100)).Times(0);

	SSD ssd;
	ssd.setFile(&file);
	ssd.read(-1);
	ssd.read(100);
}

//안써진 곳에 read
