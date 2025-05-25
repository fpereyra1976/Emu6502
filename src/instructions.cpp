#include "common.hpp"
#include "instructions.hpp"

namespace CPU6502 {
    Byte Reset(Registers &reg, Memory &mem){
        return reg.PC;
    }

    Byte NOP(Registers &reg, Memory &mem){
        return Byte(0);
    }

    Byte SEC(Registers &reg, Memory &mem){
        reg.UpdateCarryFlag(512); // value > 0xFF
        return Byte(0);
    }

    Byte CLC(Registers &reg, Memory &mem){
        reg.UpdateCarryFlag(128); // value < 0xFF
        return Byte(0);
    }

    Byte BRK(Registers &reg, Memory &mem){
        return Byte(0);
    }

    Byte LDA(Registers &reg, Memory &mem){
        Byte result = reg._DB;

        // Update Flags
        reg.UpdateZeroFlag(result);
        reg.UpdateNegativeFlag(result);

        reg.A = result;
        return reg.A;
    }

    Byte LDX(Registers &reg, Memory &mem){
        Byte result = reg._DB;
              
        // Update Flags
        reg.UpdateZeroFlag(result);
        reg.UpdateNegativeFlag(result);

        reg.X = result;
        return reg.X;
    }

    Byte LDY(Registers &reg, Memory &mem){
        Byte result = reg._DB;
              
        // Update Flags
        reg.UpdateZeroFlag(result);
        reg.UpdateNegativeFlag(result);

        reg.Y = result;
        return reg.Y;
    }

    Byte ADC(Registers &reg, Memory &mem) {
        // ADC A, #immediate
        // ADC A, $00

        // TODO: BCD mode not implemented
        Word sum = reg.A + reg._DB + (reg.P & static_cast<Byte>(CPU6502::StatusFlag::C));
        Byte result = static_cast<Byte>(sum & 0xFF);

        // Update Flags
        reg.UpdateZeroFlag(result);
        reg.UpdateNegativeFlag(result);
        reg.UpdateCarryFlag(sum);
        reg.UpdateOverflowFlag(reg.A, reg._DB, result);

        reg.A = result;
        return reg.A;
    }

    Byte SBC(Registers &reg, Memory &mem) {
        Word valueInverted = static_cast<Word>(~reg._DB);
        Word carryIn = reg.P & static_cast<Byte>(CPU6502::StatusFlag::C);
        Word sum = reg.A + valueInverted + carryIn;
        Byte result = static_cast<Byte>(sum & 0xFF);

        reg.UpdateZeroFlag(result);
        reg.UpdateNegativeFlag(result);
        reg.UpdateCarryFlag(sum);
        reg.UpdateOverflowFlag(reg.A, reg._DB, result);

        reg.A = result;
        return reg.A;
    }
};