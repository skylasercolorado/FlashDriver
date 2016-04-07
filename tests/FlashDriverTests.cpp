//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <IoMock.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Camax;

class FlashDriverProgramTest : public ::testing::Test
{
public:
    FlashDriverProgramTest() {}

    virtual void SetUp()
    {}

    virtual void TearDown()
    {}

private:
    IoMock ioMock_;
};

TEST_F(FlashDriverProgramTest, one)
{
    EXPECT_TRUE(true);
}
