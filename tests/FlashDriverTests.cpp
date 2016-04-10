//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <IoMock.hpp>
#include <OsTime.hpp>
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
    {
        address_ = 0x1000;
        data_ = 0xBEEF;

        cfiMemMock_ =
                {
                    {CfiField::Manufacturer,                            St},
                    {CfiField::QueryQChar,                              'Q'},
                    {CfiVoltages::VppMin,                               0x27},
                    {CfiField::ExtendedTableAddress,                    extendedTableAddr_},
                    {CfiExtendedField::QueryPChar + extendedTableAddr_, 'P'}
                };
    }

    virtual void TearDown()
    {}

    IoMock ioMock_;
    FlashDriver flashDriver_;
    ioAddress address_;
    ioData data_;
    CfiMem cfiMemMock_;
    const ioAddress extendedTableAddr_ = 0x35;
};

TEST_F(FlashDriverProgramTest, WriteSucceeds_ReadyImmediately)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));
    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
                .WillOnce(Return(FlashStatus::Ready));
    EXPECT_CALL(ioMock_, IoRead(address_))
                .WillOnce(Return(data_));

    EXPECT_EQ(FlashResult::Success, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteSucceeds_NotReadyImmediately)
{
    OsTime::initializeTime(0, 500);

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Undefined))
            .WillOnce(Return(FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoRead(address_)).WillOnce(Return(data_));

    EXPECT_EQ(FlashResult::Success, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFailsVppError)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::VppError | FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Reset));

    EXPECT_EQ(FlashResult::Vpp_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFailsProgramError)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::ProgramError | FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Reset));

    EXPECT_EQ(FlashResult::Program_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFailsProtectedBlockError)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::ProtectedBlockError | FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Reset));

    EXPECT_EQ(FlashResult::ProtectedBlock_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFailsUnknownBlockError)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::Unknown | FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Reset));

    EXPECT_EQ(FlashResult::Unknown_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFailsReadBackError)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(FlashStatus::Ready));

    EXPECT_CALL(ioMock_, IoRead(address_))
                .WillOnce(Return(data_ - 1));

    EXPECT_EQ(FlashResult::ReadBack_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteSucceeds_IgnoresOtherBitsUntilReady)
{
    OsTime::initializeTime(0, 250);

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));
    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillOnce(Return(~FlashStatus::Ready))
            .WillOnce(Return(FlashStatus::Ready));
    EXPECT_CALL(ioMock_, IoRead(address_))
            .WillOnce(Return(data_));

    EXPECT_EQ(FlashResult::Success, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, GetTimeTest)
{
    OsTime::initializeTime(0, 250);

    EXPECT_EQ(0, OsTime::GetMicroSeconds());
    EXPECT_EQ(250, OsTime::GetMicroSeconds());
    EXPECT_EQ(500, OsTime::GetMicroSeconds());
}

TEST_F(FlashDriverProgramTest, WriteFails_Timeout)
{
    OsTime::initializeTime(0, 500);

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));
    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillRepeatedly(Return(~FlashStatus::Ready));

    EXPECT_EQ(FlashResult::Timeout_Error, flashDriver_.Program(address_, data_));
}

TEST_F(FlashDriverProgramTest, WriteFails_TimeoutAtEndOfTime)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::Write));
    EXPECT_CALL(ioMock_, IoWrite(address_, data_));

    OsTime::initializeTime(0xFFFFFFFFFFFFFFF0, 250);

    EXPECT_CALL(ioMock_, IoRead(FlashRegisters::Status))
            .WillRepeatedly(Return(~FlashStatus::Ready));

    EXPECT_EQ(FlashResult::Timeout_Error, flashDriver_.Program(address_, data_));
}
using ::testing::_;
using ::testing::Invoke;
using ::testing::AnyNumber;

TEST_F(FlashDriverProgramTest, ReturnMaps)
{
    typedef std::map<ioAddress, ioData> CfiData;

    CfiData cfiData;

    cfiData.insert(std::make_pair<ioAddress, ioData>(0, 10));
    cfiData.insert(std::make_pair<ioAddress, ioData>(1, 20));
    cfiData.insert(std::make_pair<ioAddress, ioData>(2, 30));

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::CfiQuery))
            .Times(AnyNumber());
    EXPECT_CALL(ioMock_, IoRead(_))
            .WillRepeatedly(Invoke([&](ioAddress address)
                                   {
                                       return cfiData.find(address)->second;
                                   }
            ));

    EXPECT_EQ(10, flashDriver_.CfiRead(0));
    EXPECT_EQ(20, flashDriver_.CfiRead(1));
    EXPECT_EQ(30, flashDriver_.CfiRead(2));
}

using ::testing::Sequence;

TEST_F(FlashDriverProgramTest, ReturnMapsStrictOrder)
{
    typedef std::map<ioAddress, ioData> CfiData;

    CfiData cfiData;

    cfiData.insert(std::make_pair<ioAddress, ioData>(0, 10));
    cfiData.insert(std::make_pair<ioAddress, ioData>(1, 20));
    cfiData.insert(std::make_pair<ioAddress, ioData>(2, 30));

    Sequence s;

    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::CfiQuery))
            .Times(AnyNumber())
            .InSequence(s);
    EXPECT_CALL(ioMock_, IoRead(_))
            .InSequence(s)
            .WillRepeatedly(Invoke([&](ioAddress address)
                                   {
                                       return cfiData.find(address)->second;
                                   }
            ));

    EXPECT_EQ(30, flashDriver_.CfiRead(2));
}

TEST_F(FlashDriverProgramTest, CfiFieldsReturnsOk)
{
    EXPECT_CALL(ioMock_, IoWrite(FlashRegisters::Control, FlashCommands::CfiQuery))
            .Times(AnyNumber());
    EXPECT_CALL(ioMock_, IoRead(_))
                .WillRepeatedly(Invoke([&](ioAddress address)
                                 {
                                     return cfiMemMock_.find(address)->second;
                                 }));

    EXPECT_EQ(Manufacturers::St, flashDriver_.CfiRead(CfiField::Manufacturer));
    EXPECT_EQ(2.7, flashDriver_.CfiRead(CfiVoltages::VppMin));
}
