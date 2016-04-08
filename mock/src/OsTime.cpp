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
    return (microSeconds_ += incrementMicroSeconds_);
}

void OsTime::initializeTime(uint64_t initialMicroSeconds, uint64_t incrementMicroSeconds)
{
    incrementMicroSeconds_ = incrementMicroSeconds;
    microSeconds_ = initialMicroSeconds;
}

