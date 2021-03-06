//
// Created by duncan on 4/6/16.
//

#ifndef FLASHDRIVER_IO_HPP
#define FLASHDRIVER_IO_HPP

#include <cstdint>

namespace Camax
{
    typedef uint32_t ioAddress;
    typedef uint16_t ioData;

    enum FlashRegisters : ioAddress
    {
        Control             = 0,
        Status              = 0
    };

    enum FlashCommands : ioData
    {
        Write               = 0x40,
        Reset               = 0xFF,
        CfiQuery            = 0x98
    };

    enum FlashStatus : ioData
    {
        Ready               = 1 << 7,
        VppError            = 1 << 3,
        ProgramError        = 1 << 4,
        ProtectedBlockError = 1 << 1,
        Unknown             = 1 << 10,
        Undefined           = 0
    };

    enum FlashResult
    {
        Success,
        Vpp_Error,
        Program_Error,
        ProtectedBlock_Error,
        Unknown_Error,
        ReadBack_Error,
        Timeout_Error
    };

    class IIo
    {
    public:
        virtual ~IIo() {}
        virtual ioData IoRead(ioAddress offset) = 0;
        virtual void IoWrite(ioAddress offset, ioData data) = 0;
    };
}

#endif //FLASHDRIVER_IO_HPP
