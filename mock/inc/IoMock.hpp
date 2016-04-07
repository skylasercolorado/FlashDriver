//
// Created by duncan on 4/6/16.
//

#ifndef FLASHDRIVER_IOMOCK_HPP
#define FLASHDRIVER_IOMOCK_HPP

#include "gmock/gmock.h"
#include "IIo.hpp"

namespace Camax
{
    class IoMock : public IIo
    {
    public:
        //virtual ioData IoRead(ioAddress offset);
        //virtual void IoWrite(ioAddress offset, ioData data);

        MOCK_METHOD1(IoRead, ioData(ioAddress offset));
        MOCK_METHOD2(IoWrite, void(ioAddress offset, ioData data));
    };
}
#endif //FLASHDRIVER_IOMOCK_HPP
