//
// Created by duncan on 4/9/16.
//

#ifndef FLASHDRIVER_CFI_HPP
#define FLASHDRIVER_CFI_HPP

namespace Camax
{
    enum CfiField : ioAddress
    {
        Manufacturer            = 0,
        DeviceCode              = 1,
        QueryStringQ            = 0x10,
        VddMin                  = 0x1B,
        VppMin                  = 0x1D,
        DeviceSize              = 0x27,
        ExtendedTableAddress    = 0x15
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

    enum ExtendedField : ioAddress
    {
        QueryStringP            = 0,
        Features                = 5
    };

    enum SupportedFeatures : uint32_t
    {
        ChipErase               = 1 << 0,
        SuspendErase            = 1 << 1,
        SuspendProgram          = 1 << 2
    };

    typedef std::map<ioAddress, ioData> CfiMem;

    CfiMem cfiMem =
            {
                    {Manufacturer,          0x20},
                    {QueryStringQ,          0x51}
            };

    CfiMem extQueryMem =
            {
                    {QueryStringP,          0x50}
            };
}

#endif //FLASHDRIVER_CFI_HPP
