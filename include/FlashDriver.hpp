//
// Created by duncan on 4/6/16.
//

#ifndef FLASHDRIVER_FLASHDRIVER_HPP
#define FLASHDRIVER_FLASHDRIVER_HPP

#include "IIo.hpp"

namespace Camax
{
    class FlashDriver
    {
    public:
        FlashDriver(IIo &io) : io_(io) {}
        ~FlashDriver() {}
        FlashResult Program(ioAddress address, ioData data);
        ioData CfiQuery(ioAddress address);

        const uint64_t Timeout = 2000; // useconds

    private:
        IIo &io_;
        FlashResult processError(ioData &status, IIo &io);
    };
}
#endif //FLASHDRIVER_FLASHDRIVER_HPP
