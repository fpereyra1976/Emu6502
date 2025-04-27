#ifndef __REGISTERS_HPP
#define __REGISTERS_HPP

#include"common.hpp"

namespace CPU6502{   
    enum class StatusFlag : std::uint8_t {
        N   = 0b10000000,
        O   = 0b01000000,
        B   = 0b00010000,
        D   = 0b00001000,
        I   = 0b00000100,
        Z   = 0b00000010,
        C   = 0b00000001,
    };

class Registers{
    public:
        Word        _TMP;
        Word        _AB;
        Byte        _DB;
        Byte        _IR;
        Byte        _ADL;
        Byte        _ADH;
        Bit         _RW;
        Byte        A;
        Byte        X;
        Byte        Y;
        Word        SP;
        Word        PC;
        Byte        P;
};
}
#endif