#ifndef __COMMON_HPP_
#define __COMMON_HPP_

#include <cstdint>
#include <iostream>

namespace CPU6502 {
    using Byte = std::uint8_t;
    using Word = std::uint16_t;

    enum class Bit : std::uint8_t {
        On = 0x01,
        Off = 0x00
    };

    inline std::ostream& operator<<(std::ostream& os, Bit b) {
        os << static_cast<bool>(b);
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, Byte b) {
        os << static_cast<int>(b);
        return os;
    }

    // Me gustaria refefinirlo para WORD pero no se puede :-(
}

#endif // __COMMON_HPP_
