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

TEST(SSDTest, WriteTestCallOnce) {
	MockFile file;
	SSD ssd;
	ssd.setFile(&file);
	EXPECT_CALL(file, write(1, "0x12345678"))
		.Times(1);

	ssd.write(1, "0x12345678");
}
TEST(SSDTest, WriteTestCall3Times) {
	MockFile file;
	SSD ssd;
	ssd.setFile(&file);
	EXPECT_CALL(file, write(_, _))
		.Times(3);

	ssd.write(1, "0x12345678");
	ssd.write(2, "0x12345678");
	ssd.write(3, "0x12345678");
}