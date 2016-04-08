//
// Created by duncan on 4/8/16.
//

#ifndef FLASHDRIVER_IOSTIME_HPP
#define FLASHDRIVER_IOSTIME_HPP

namespace Camax
{
    class IOsTime
    {
    public:
        virtual uint64_t GetMicroSeconds() = 0;
    };
}
#endif //FLASHDRIVER_IOSTIME_HPP
