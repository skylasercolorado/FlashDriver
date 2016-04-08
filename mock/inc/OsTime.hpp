//
// Created by duncan on 4/8/16.
//

#ifndef FLASHDRIVER_OSTIME_HPP
#define FLASHDRIVER_OSTIME_HPP

// This is a stub (link time).
namespace Camax
{
    class OsTime
    {
    public:
        static uint64_t GetMicroSeconds();
        static void initializeTime(uint64_t initialMicroSeconds, uint64_t incrementMicroSeconds);

    private:
        static uint64_t microSeconds_;
        static uint64_t initialMicroSeconds_;
        static uint64_t incrementMicroSeconds_;
    };
}
#endif //FLASHDRIVER_OSTIME_HPP
