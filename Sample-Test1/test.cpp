//#include "pch.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project12/DeviceDriver.cpp" // cpp include되어야함
#include "../Project12/App.cpp"
#include <stdexcept>

using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class FlashMockFixture : public testing::Test
{
public:

protected:
	FlashMock mk;
};

TEST(TestCaseName, readTest) {
	FlashMock mk;
	DeviceDriver dd(&mk);
	//5회 read되야 pass야
	EXPECT_CALL(mk, read).Times(5);

	dd.read(0xA);
}

TEST(TestCaseName, readFail) {
	FlashMock mk;
	DeviceDriver dd(&mk);
	//5회 read되야 pass야
	EXPECT_CALL(mk, read).WillOnce(Return(0xA)).WillOnce(Return(0xA)).WillOnce(Return(0xA)).WillOnce(Return(0xA)).WillRepeatedly(Return(0xB));

	EXPECT_THROW(dd.read(0xA), std::exception);
}

TEST(TestCaseName, writeTest) {
	FlashMock mk; // NiceMock<FlashMock> mk;
	DeviceDriver dd(&mk);
	EXPECT_CALL(mk, read).WillRepeatedly(Return(0xFF));

	dd.write(0xA, 3);
}

TEST(TestCaseName, blankException) {
	FlashMock mk; // NiceMock<FlashMock> mk;
	DeviceDriver dd(&mk);

	EXPECT_CALL(mk, read(0xDD)).WillRepeatedly(Return(0xFA));
	EXPECT_THROW(dd.write(0xDD, 3), std::exception);
}

TEST(TestCaseName, app_read_and_print) {
	FlashMock mk; // NiceMock<FlashMock> mk;
	DeviceDriver dd(&mk);
	App app(&dd);

	EXPECT_CALL(mk, read(0x0)).WillRepeatedly(Return(0xA));
	EXPECT_CALL(mk, read(0x1)).WillRepeatedly(Return(0xB));
	EXPECT_CALL(mk, read(0x2)).WillRepeatedly(Return(0xC));
	EXPECT_CALL(mk, read(0x3)).WillRepeatedly(Return(0xD));
	EXPECT_CALL(mk, read(0x4)).WillRepeatedly(Return(0xE));
	app.ReadAndPrint(0x0, 0x4);
}

TEST(TestCaseName, write_all) {
	NiceMock<FlashMock> mk; //FlashMock mk; 
	DeviceDriver dd(&mk);
	App app(&dd);

	EXPECT_CALL(mk, read(0x0)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, read(0x1)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, read(0x2)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, read(0x3)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mk, read(0x4)).WillRepeatedly(Return(0xFF));
	app.WriteAll(0xA);

	EXPECT_CALL(mk, read(0x0)).WillRepeatedly(Return(0xA));
	EXPECT_CALL(mk, read(0x1)).WillRepeatedly(Return(0xA));
	EXPECT_CALL(mk, read(0x2)).WillRepeatedly(Return(0xA));
	EXPECT_CALL(mk, read(0x3)).WillRepeatedly(Return(0xA));
	EXPECT_CALL(mk, read(0x4)).WillRepeatedly(Return(0xA));
	app.ReadAndPrint(0x0, 0x4);
}