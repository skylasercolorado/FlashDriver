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

    class IIo
    {
        virtual ioData IoRead(ioAddress offset) = 0;
        virtual void IoWrite(ioAddress offset, ioData data) = 0;
    };
}

#endif //FLASHDRIVER_IO_HPP
