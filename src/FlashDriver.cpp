//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>

using namespace Camax;


bool FlashDriver::Program(ioAddress address, ioData data)
{
    ioData status;

    io_.IoWrite(FlashRegisters::Control, FlashCommands::Write);
    io_.IoWrite(address, data);

    while(!((status = io_.IoRead(FlashRegisters::Status)) & FlashStatus::Ready));

    if(status & FlashStatus::VppError)
    {
        io_.IoWrite(FlashRegisters::Control, FlashCommands::Reset);
        return false;
    }

    return io_.IoRead(address) == data ? true : false;
}
