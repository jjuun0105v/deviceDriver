//#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project12/DeviceDriver.cpp" // cpp include�Ǿ����
//#include "../Project12/FlashMemoryDevice.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

};

TEST(TestCaseName, readTest) {
	FlashMock mk;
	DeviceDriver dd(&mk);
	//5ȸ read�Ǿ� pass��
	EXPECT_CALL(mk, read).Times(5);

	dd.read(0xA);
}

TEST(TestCaseName, writeTest) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	// write�ƴ��� ����
	dd.write(0xA, 3);
}