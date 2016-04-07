//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>

using namespace Camax;


bool FlashDriver::Program(ioAddress address, ioData data)
{
    io_.IoWrite(FlashRegisters::Control, FlashCommands::Write);
    io_.IoWrite(address, data);
    if (io_.IoRead(FlashRegisters::Control) == FlashStatus::Ready)
        return io_.IoRead(address) == data ? true : false;
    else
        return false;
}
