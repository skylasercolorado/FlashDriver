//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <IoMock.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Camax;
using ::testing::AtLeast;
using ::testing::Return;

class FlashDriverProgramTest : public ::testing::Test
{
public:
    FlashDriverProgramTest() : flashDriver_(ioMock_)
    {}

    virtual void SetUp()
    {}

    virtual void TearDown()
    {}

    IoMock ioMock_;
    FlashDriver flashDriver_;
};

//TEST_F(FlashDriverProgramTest, WriteSucceeds_ReadyImmediately)
//{
//    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
//    EXPECT_CALL(ioMock_, IoWrite(0x1000, 0xBEEF));
//    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
//                .WillOnce(Return(FlashStatus::Ready));
//    EXPECT_CALL(ioMock_, IoRead(0x1000))
//                .WillOnce(Return(0xBEEF));
//
//    EXPECT_TRUE(flashDriver_.Program(0x1000, 0xBEEF));
//}

TEST_F(FlashDriverProgramTest, WriteSucceeds_NotReadyImmediately)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(0x1000, 0xBEEF));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoRead(0x1000)).WillOnce(Return(0xBEEF));

    EXPECT_TRUE(flashDriver_.Program(0x1000, 0xBEEF));
}
