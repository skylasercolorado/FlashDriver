//
// Created by duncan on 4/9/16.
//

#ifndef FLASHDRIVER_CFI_HPP
#define FLASHDRIVER_CFI_HPP

#include <map>
#include "IIo.hpp"

namespace Camax
{
    namespace Cfi
    {
        /*******************************************
         * CFI Memory Map
         *******************************************/
        enum CfiField : ioAddress {
            Manufacturer = 0,
            DeviceCode = 1,
            QueryQChar = 0x10,
            DeviceSize = 0x27,
            ExtendedTableOffset = 0x15
        };

        enum CfiVoltages : ioAddress {
            VddMin = 0x1B,
            VppMin = 0x1D
        };

        enum CfiExtendedField : ioAddress {
            QueryPChar = 0,
            Features = 5
        };

        enum SupportedFeatures : uint32_t {
            ChipErase = 1 << 0,
            SuspendErase = 1 << 1,
            SuspendProgram = 1 << 2
        };

        /****************************************************************************
         * CFI specifications for STMicroelectronics' M28W160ECx 16 Mbit Flash Memory
         ****************************************************************************/

        enum Manufacturers : ioData {
            St = 0x20,
            Intel = 0x21
        };

        enum DeviceCodes : ioData {
            Top = 0x88CE,
            Bottom = 0x88CF
        };

        const ioData QueryQCharReq      = 'Q';
        const double VppMinReq          = 11.4;
        const double VppMaxReq          = 12.6;

        const double VddMinReq          = 2.7;
        const double VddMaxReq          = 3.6;

        const ioData QueryPCharReq = 'P';
    }
}

#endif //FLASHDRIVER_CFI_HPP
