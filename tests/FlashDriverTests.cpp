//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <IoMock.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Camax;
using ::testing::AtLeast;

class FlashDriverProgramTest : public ::testing::Test
{
public:
    FlashDriverProgramTest() //: flashDriver_(ioMock_)
    {}

    virtual void SetUp()
    {}

    virtual void TearDown()
    {
       // delete ioMock_;
    }

    IoMock ioMock_;
    //FlashDriver flashDriver_;
};

TEST_F(FlashDriverProgramTest, one)
{
//    EXPECT_CALL(ioMock_, IoWrite(0x01, 0x02))
//            .Times(AtLeast(1));

    //flashDriver_.Program(0x01, 0x02);
    EXPECT_TRUE(true);
}
