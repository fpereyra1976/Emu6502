#ifndef __REGISTERS_HPP
#define __REGISTERS_HPP

#include"common.hpp"

namespace CPU6502{   
    enum class StatusFlag : std::uint8_t {
        N   = 0b10000000, // Negative
        O   = 0b01000000, // Overflow
        B   = 0b00010000, // Break
        D   = 0b00001000, // Decimal
        I   = 0b00000100, // Interrupt Disable
        Z   = 0b00000010, // Zero
        C   = 0b00000001, // Carry
    };

class Registers{
    public:
        Word        _TMP;
        Word        _AB;
        Byte        _DB;
        Byte        _IR;
        Bit         _RW;
        Byte        A;
        Byte        X;
        Byte        Y;
        Word        SP;
        Word        PC;
        Byte        P;
    
    Registers() : 
        _TMP(0x0000), _AB(0x0000), _DB(0x00), _IR(0x00), _RW(Bit::Off),
        A(0x00), X(0x00), Y(0x00), SP(0x0000), PC(0x0000), P(0x00) {}
    

    Bit UpdateZeroFlag(Byte result){
        if (result == 0x00) {
            this->P |= static_cast<std::uint8_t>(StatusFlag::Z);  // Setea el flag Z
        } else {
            this->P &= ~static_cast<std::uint8_t>(StatusFlag::Z); // Limpia el flag Z
        }
        return this->P & static_cast<std::uint8_t>(StatusFlag::Z) ? Bit::On : Bit::Off;
    }

    Bit UpdateNegativeFlag(Byte result){
        if (result & 0x80) {
            this->P |= static_cast<std::uint8_t>(StatusFlag::N);  // Setea el flag N
        } else {
            this->P &= ~static_cast<std::uint8_t>(StatusFlag::N); // Limpia el flag N
        }
        return this->P & static_cast<std::uint8_t>(StatusFlag::N) ? Bit::On : Bit::Off;
    }

    Bit UpdateCarryFlag(Word result){
        // CARRY
        if (result > 0xFF)
            this->P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::C);
        else
            this->P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::C);

        return this->P & static_cast<std::uint8_t>(StatusFlag::C) ? Bit::On : Bit::Off;
    }


    Bit UpdateOverflowFlag(Byte a ,Byte b, Byte result){
        // OVERFLOW
        if (((a ^ result) & (b ^ result) & 0x80) != 0)
            this->P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::O);
        else
            this->P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::O);
        
        return this->P & static_cast<std::uint8_t>(StatusFlag::O) ? Bit::On : Bit::Off;
    }   
};
}
#endif