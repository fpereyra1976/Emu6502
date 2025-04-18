#ifndef __COMMON_HPP_
#define __COMMON_HPP_

#include <cstdint>

namespace CPU6502{
    using Byte = std::uint8_t;
    using Word = std::uint16_t;

    enum class Bit : std::uint8_t {
        On = 0x01,
        Off = 0x00
    };
}

#endif