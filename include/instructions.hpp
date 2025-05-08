#ifndef __INSTRUCTION_HPP_
#define __INSTRUCTION_HPP_

#include<vector>
#include<map>

#include <initializer_list>

#include "common.hpp"
#include "registers.hpp"
#include "exceptions.hpp"
#include "memory.hpp"

namespace CPU6502{
    enum class Opcodes : Byte {
        RESET           = 0xFC,
        LDA_IMMEDIATE   = 0xA9,
        LDA_ZEROPAGE    = 0xA5,
        LDA_ZEROPAGE_X  = 0xB5,
        LDX_IMMEDIATE   = 0xA2,
        LDY_IMMEDIATE   = 0xA0,
        NOP_IMPLICIT    = 0xEA,
        BRK_IMPLICIT    = 0x00
    };

    enum class OperationStep : Byte {
        Reset                       = 0x01,
        FetchOpcode                 = 0x02,
        FetchOperand                = 0x03,
        FetchFirstOperandAbsolute   = 0x04,
        FetchSecondOperandAbsolute  = 0x05,
        FetchValue                  = 0x06,
        FetchIndexedAddress         = 0x07,
        FetchIndexedValue           = 0x08,
        FetchValueAbsolute          = 0x09,
    };
    
    using OperarionStepsSequence = std::vector<OperationStep>;

    class Instruction {
        private:
            Opcodes operationCode;
            OperarionStepsSequence steps;
            Byte (*action)(Registers &reg, Memory &mem) = nullptr; 
        public:
            Instruction(Opcodes opc,OperarionStepsSequence s,Byte (*a)(Registers &reg, Memory &mem) = nullptr)
                : operationCode(opc), steps(s), action(a) {}
    
            Opcodes Opcode() const { 
                return operationCode; 
            }

            Byte Execute(Registers &reg, Memory &mem) {
                if (action != nullptr) {
                    return action(reg, mem);
                }
                return 0;
            }

            std::vector<OperationStep>& Steps() { return steps; }
    };

    using InstructionSet = std::map<Byte, Instruction>;
    using OperarionStepsSequenceIterator = OperarionStepsSequence::const_iterator;

    Byte Reset(Registers &reg, Memory &mem);
    Byte NOP(Registers &reg, Memory &mem);
    Byte BRK(Registers &reg, Memory &mem);
    Byte LDA(Registers &reg, Memory &mem);
    Byte LDX(Registers &reg, Memory &mem);
    Byte LDY(Registers &reg, Memory &mem);

    const Instruction RESET_SIGNAL = Instruction(
        Opcodes::RESET, 
        // No es un opcode oficial, lo aprovecho para que el reser
        // se comporte de modo similar a un opcode
        { 
            OperationStep::Reset,
            OperationStep::FetchFirstOperandAbsolute,
            OperationStep::FetchSecondOperandAbsolute
        },
        Reset
    );

    const Instruction BRK_IMPLICIT = Instruction(
        Opcodes::BRK_IMPLICIT, // opcode de LDA #immediate
        {},
        BRK 
    );

    const Instruction NOP_IMPLICIT = Instruction(
        Opcodes::NOP_IMPLICIT, // opcode de LDA #immediate
        {},
        NOP 
    );

    const Instruction LDA_IMMEDIATE = Instruction(
        Opcodes::LDA_IMMEDIATE, // opcode de LDA #immediate
        { 
            OperationStep::FetchOperand, 
        },
        LDA
    );

    const Instruction LDA_ZEROPAGE = Instruction(
        Opcodes::LDA_ZEROPAGE, // opcode de LDA #immediate
        { 
            OperationStep::FetchOperand,
            OperationStep::FetchValue 
        },
        LDA
    );

    const Instruction LDA_ZEROPAGE_X = Instruction(
        Opcodes::LDA_ZEROPAGE_X, // opcode de LDA #immediate
        { 
            OperationStep::FetchOperand,
            OperationStep::FetchIndexedAddress,
            OperationStep::FetchIndexedValue 
        },
        LDA
    );
    
    const Instruction LDX_IMMEDIATE = Instruction(
        Opcodes::LDX_IMMEDIATE, // opcode de LDA #immediate
        { 
            OperationStep::FetchOperand 
        },
        LDX
    );

    const Instruction LDY_IMMEDIATE = Instruction(
        Opcodes::LDY_IMMEDIATE, // opcode de LDA #immediate
        { 
            OperationStep::FetchOperand 
        },
        LDY
    );

    const InstructionSet INSTRUCTION_SET = {
        { 0x00, BRK_IMPLICIT },
        { 0xEA, NOP_IMPLICIT },
        { 0xA5, LDA_ZEROPAGE },
        { 0xB5, LDA_ZEROPAGE_X },
        { 0xA5, LDA_IMMEDIATE },
        { 0xA2, LDX_IMMEDIATE },
        { 0xA9, LDY_IMMEDIATE },
        { 0xEA, NOP_IMPLICIT },
        { 0xA9, LDA_IMMEDIATE },
        { 0xA2, LDX_IMMEDIATE },
        { 0xA9, LDY_IMMEDIATE },
        { 0xFC, RESET_SIGNAL }

        // ...
    };
}

#endif