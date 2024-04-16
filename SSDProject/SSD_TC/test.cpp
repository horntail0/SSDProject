#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/File.cpp"

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