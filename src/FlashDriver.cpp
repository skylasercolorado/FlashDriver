//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>
#include <OsTime.hpp>
#include <iostream>

using namespace Camax;
using namespace std;

FlashResult FlashDriver::Program(ioAddress address, ioData data)
{
    ioData status;

    io_.IoWrite(FlashRegisters::Control, FlashCommands::Write);
    io_.IoWrite(address, data);

    uint64_t startTime = OsTime::GetMicroSeconds();

    while(!((status = io_.IoRead(FlashRegisters::Status)) & FlashStatus::Ready))
    {
        uint64_t currentTime = OsTime::GetMicroSeconds();

        cout.setf(ios::hex, ios::basefield);
        cout.setf(ios::showbase);

        std::cout << "\ncurrentTime: " << unsigned(currentTime) << ". startTime: " << unsigned(startTime) << ".";
        std::cout << " currentTime - startTime = " << unsigned(currentTime - startTime) << ".\n";
        
        cout.unsetf(ios::hex);

        if (currentTime - startTime >= Timeout)
            return FlashResult::Timeout_Error;
    }

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