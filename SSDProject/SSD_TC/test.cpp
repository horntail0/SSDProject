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