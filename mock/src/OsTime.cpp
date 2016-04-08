//
// Created by duncan on 4/8/16.
//
#include <cstdint>
#include "OsTime.hpp"

using namespace Camax;

uint64_t OsTime::microSeconds_ = 0;
uint64_t OsTime::initialMicroSeconds_ = 0;
uint64_t OsTime::incrementMicroSeconds_ = 500;

uint64_t OsTime::GetMicroSeconds()
{
    microSeconds_ = initialMicroSeconds_;
    initialMicroSeconds_ += incrementMicroSeconds_;
    return (microSeconds_);
}

void OsTime::initializeTime(uint64_t initialMicroSeconds, uint64_t incrementMicroSeconds)
{
    incrementMicroSeconds_ = incrementMicroSeconds;
    microSeconds_ = initialMicroSeconds;
}

