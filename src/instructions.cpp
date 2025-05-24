#include "common.hpp"
#include "instructions.hpp"

namespace CPU6502 {
    Byte Reset(Registers &reg, Memory &mem){
        reg.PC = reg._TMP;
        return reg.PC;
    }

    Byte NOP(Registers &reg, Memory &mem){
        return Byte(0);
    }

    Byte BRK(Registers &reg, Memory &mem){
        return Byte(0);
    }

    Byte LDA(Registers &reg, Memory &mem){
        reg.A = reg._DB;
        // Update Flags
        // Actualizar el flag Z (Zero)
        if (reg.A == 0x00) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);  // Setea el flag Z
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z); // Limpia el flag Z
        }

        // Actualizar el flag N (Negative)
        if (reg.A & 0x80) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N);  // Setea el flag N
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N); // Limpia el flag N
        }
        return reg.A;
    }

    Byte LDX(Registers &reg, Memory &mem){
        reg.X = reg._DB;
        // Update Flags
        // Actualizar el flag Z (Zero)
        if (reg.X == 0x00) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);  // Setea el flag Z
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z); // Limpia el flag Z
        }
        // Actualizar el flag N (Negative)
        if (reg.X & 0x80) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N);  // Setea el flag N
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N); // Limpia el flag N
        }
        return reg.X;
    }

    Byte LDY(Registers &reg, Memory &mem){
        reg.Y = reg._DB;

        // Update Flags
        // Actualizar el flag Z (Zero)
        if (reg.Y == 0x00) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);  // Setea el flag Z
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z); // Limpia el flag Z
        }
        // Actualizar el flag N (Negative)
        if (reg.Y & 0x80) {
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N);  // Setea el flag N
        } else {
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N); // Limpia el flag N
        }
        return reg.Y;
    }

    Byte ADC(Registers &reg, Memory &mem) {
        Word sum = reg.A + reg._DB + (reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::C));
        Byte result = static_cast<Byte>(sum & 0xFF);

        // CARRY
        if (sum > 0xFF)
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::C);
        else
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::C);

        // ZERO
        if (result == 0x00)
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);
        else
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);

        // NEGATIVE (usa el resultado, no reg.A)
         if (result & 0x80)
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N);
        else
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N);

        // OVERFLOW
        if (((reg.A ^ result) & (reg._DB ^ result) & 0x80) != 0)
            reg.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::O);
        else
            reg.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::O);

        reg.A = result;
        return reg.A;
    }
};