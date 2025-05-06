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
    enum class OperationStep : Byte {
        Reset               = 0x01,
        FetchOpcode         = 0x02,
        FetchOperand        = 0x03,
        FetchFirstOperand   = 0x04,
        FetchSecondOperand  = 0x05,
        FetchValue          = 0x06,
        FetchIndexedAddress = 0x07,
        FetchIndexedValue   = 0x08,
        FetchValueAbsolute  = 0x09,
        LoadProgramCounter  = 0x0A,
    };

    enum class AddressingMode : Byte {
        IMPLICIT            = 0x01,
        IMMEDIATE           = 0x02,   
        ZEROPAGE            = 0x03,
        ABSOLUTE            = 0x04,
        INDIRECT            = 0x05,
        INDEXED             = 0x06
    };
    
    using OperarionStepsSequence = std::vector<OperationStep>;

    class Instruction {
        private:
            Byte operationCode;
            AddressingMode addressingMode;
            OperarionStepsSequence steps;
            Byte (*action)(Registers &reg, Memory &mem) = nullptr; 
        public:
            Instruction(Byte opc, AddressingMode m ,OperarionStepsSequence s,Byte (*a)(Registers &reg, Memory &mem) = nullptr)
                : operationCode(opc), addressingMode(m) ,steps(s), action(a) {}
    
            Byte Opcode() const { 
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
        0xFC , 
        // No es un opcode oficial, lo aprovecho para que el reser
        // se comporte de modo similar a un opcode
        AddressingMode::ABSOLUTE,
        { 
            OperationStep::Reset,
            OperationStep::FetchFirstOperand,
            OperationStep::FetchSecondOperand,
        },
        Reset
    );

    const Instruction BRK_IMPLICIT = Instruction(
        0xea, // opcode de LDA #immediate
        AddressingMode::IMPLICIT,
        {},
        BRK 
    );

    const Instruction NOP_IMPLICIT = Instruction(
        0xea, // opcode de LDA #immediate
        AddressingMode::IMPLICIT,
        {},
        NOP 
    );

    const Instruction LDA_IMMEDIATE = Instruction(
        0xa9, // opcode de LDA #immediate
        AddressingMode::IMMEDIATE,
        { 
            OperationStep::FetchOperand, 
        },
        LDA
    );

    const Instruction LDA_ZEROPAGE = Instruction(
        0xa5, // opcode de LDA #immediate
        AddressingMode::ZEROPAGE,
        { 
            OperationStep::FetchOperand,
            OperationStep::FetchValue 
        },
        LDA
    );

    const Instruction LDA_ZEROPAGE_X = Instruction(
        0xb5, // opcode de LDA #immediate
        AddressingMode::ZEROPAGE,
        { 
            OperationStep::FetchOperand,
            OperationStep::FetchIndexedAddress,
            OperationStep::FetchIndexedValue 
        },
        LDA
    );
    

    const Instruction LDX_IMMEDIATE = Instruction(
        0xa2, // opcode de LDA #immediate
        AddressingMode::IMMEDIATE,
        { 
            OperationStep::FetchOperand 
        },
        LDX
    );

    const Instruction LDY_IMMEDIATE = Instruction(
        0xa0, // opcode de LDA #immediate
        AddressingMode::IMMEDIATE,
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