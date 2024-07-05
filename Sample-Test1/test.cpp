//#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project12/DeviceDriver.cpp" // cpp include되어야함
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
	//5회 read되야 pass야
	EXPECT_CALL(mk, read).Times(5);

	dd.read(0xA);
}

TEST(TestCaseName, writeTest) {
	FlashMock mk;
	DeviceDriver dd(&mk);

	// write됐는지 여부
	dd.write(0xA, 3);
}