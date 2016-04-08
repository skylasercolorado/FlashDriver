//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>

using namespace Camax;

FlashResult FlashDriver::Program(ioAddress address, ioData data)
{
    ioData status;

    io_.IoWrite(FlashRegisters::Control, FlashCommands::Write);
    io_.IoWrite(address, data);

    while(!((status = io_.IoRead(FlashRegisters::Status)) & FlashStatus::Ready));

    if(status & ~FlashStatus::Ready)
    {
        return processError(status, io_);
//        io_.IoWrite(FlashRegisters::Control, FlashCommands::Reset);
//
//        if(status & FlashStatus::VppError)
//            return FlashResult::Vpp_Error;
//        else if(status & FlashStatus::ProgramError)
//            return FlashResult::Program_Error;
//        else if(status & FlashStatus::ProtectedBlockError)
//            return FlashResult::ProtectedBlock_Error;
//        else
//            return FlashResult::Unknown_Error;
    }

    return io_.IoRead(address) == data ? FlashResult::Success : FlashResult::ReadBack_Error;
}

FlashResult FlashDriver::processError(ioData &status, IIo &io)
{
    io.IoWrite(FlashRegisters::Control, FlashCommands::Reset);

    if (status & FlashStatus::VppError)
        return FlashResult::Vpp_Error;
    else if (status & FlashStatus::ProgramError)
        return FlashResult::Program_Error;
    else if (status & FlashStatus::ProtectedBlockError)
        return FlashResult::ProtectedBlock_Error;
    else
        return FlashResult::Unknown_Error;
}