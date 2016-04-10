//
// Created by duncan on 4/9/16.
//

#ifndef FLASHDRIVER_CFI_HPP
#define FLASHDRIVER_CFI_HPP

#include <map>
#include "IIo.hpp"

namespace Camax
{
    enum CfiField : ioAddress
    {
        Manufacturer            = 0,
        DeviceCode              = 1,
        QueryQChar              = 0x10,
        DeviceSize              = 0x27,
        ExtendedTableAddress    = 0x15
    };

    enum CfiVoltages : ioAddress
    {
        VddMin                  = 0x1B,
        VppMin                  = 0x1D
    };

    enum Manufacturers : ioData
    {
        St                      = 0x20,
        Intel                   = 0x21
    };

    enum DeviceCodes : ioData
    {
        Top                     = 0x88CE,
        Bottom                  = 0x88CF
    };

    enum CfiExtendedField : ioAddress
    {
        QueryPChar              = 0,
        Features                = 5
    };

    enum SupportedFeatures : uint32_t
    {
        ChipErase               = 1 << 0,
        SuspendErase            = 1 << 1,
        SuspendProgram          = 1 << 2
    };

    typedef std::map<ioAddress, ioData> CfiMem;

//    const ioAddress extendedTableAddr = 0x35;

//    CfiMem cfiMem =
//            {
//                    {Manufacturer,          St},
//                    {QueryQChar,            'Q'},
//                    {ExtendedTableAddress,  extendedTableAddr}
//            };
//
//    CfiMem extMem =
//            {
//                    {QueryPChar,            'P'}
//            };
//
//    CfiMem mock =
//            {
//                    {CfiField::Manufacturer,                            St},
//                    {CfiField::QueryQChar,                              'Q'},
//                    {CfiField::ExtendedTableAddress,                    extendedTableAddr},
//                    {CfiExtendedField::QueryPChar + extendedTableAddr,     'P'}
//            };
}

#endif //FLASHDRIVER_CFI_HPP
