#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "../SSD/SSDInterface.cpp"

using namespace std;

class MockSSD : public SSDInterface {
public:
	MOCK_METHOD(string, read, (int LBA), (override));
	MOCK_METHOD(void, write, (int LBA, string data), (override));
};

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}