//
// Created by duncan on 4/6/16.
//

#include <FlashDriver.hpp>

using namespace Camax;


bool FlashDriver::Program(ioAddress address, ioData data)
{
    io_.IoWrite(address, data);
    return true;
}
