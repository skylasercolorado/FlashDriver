//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <OsTime.hpp>

using namespace Camax;

FlashResult FlashDriver::Program(ioAddress address, ioData data)
{
    ioData status;

    io_.IoWrite(FlashRegisters::Control, FlashCommands::Write);
    io_.IoWrite(address, data);

    uint64_t startTime = OsTime::GetMicroSeconds();

    while(!((status = io_.IoRead(FlashRegisters::Status)) & FlashStatus::Ready))
        if(OsTime::GetMicroSeconds() - startTime >= Timeout)
            return FlashResult::Timeout_Error;

    if(status & ~FlashStatus::Ready)
        return processError(status, io_);

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

ioData FlashDriver::CfiQuery(ioAddress address)
{
    io_.IoWrite(FlashRegisters::Control, FlashCommands::CfiQuery);

    return io_.IoRead(address);
}

