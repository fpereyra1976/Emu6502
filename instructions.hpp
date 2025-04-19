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
    enum class OperationTarget : Byte {
        Nil     = 0x00,
        A       = 0x01,
        X       = 0x02,
        Y       = 0x08,
        TMP     = 0x20,
        ADL     = 0x40,
        ADH     = 0x80,
        MEMORY  = 0x80
    };
    
    enum class OperationType : u_int8_t {
        Reset           = 0x00,
        FetchOpcode     = 0x01,
        FetchOperand    = 0x02
    };

    class Operation{
        private:
            OperationType type;
            OperationTarget target;
        public:
        constexpr Operation(OperationType ty, OperationTarget tg)
        : type(ty), target(tg) {}
        constexpr OperationType getType() const { return type; }
        constexpr OperationTarget getTarget() const { return target; }   
    };
    
    constexpr Operation RESET(OperationType::Reset, OperationTarget::Nil);
    constexpr Operation FETCH_OPCODE(OperationType::FetchOpcode, OperationTarget::Nil);
    constexpr Operation FETCH_OPERAND_A(OperationType::FetchOperand, OperationTarget::A);
    constexpr Operation FETCH_OPERAND_X(OperationType::FetchOperand, OperationTarget::X);
    constexpr Operation FETCH_OPERAND_Y(OperationType::FetchOperand, OperationTarget::Y);
    constexpr Operation FETCH_OPERAND_ADL(OperationType::FetchOperand, OperationTarget::ADL);
    constexpr Operation FETCH_OPERAND_ADH(OperationType::FetchOperand, OperationTarget::ADH);

    constexpr Operation JUMP(OperationType::FetchOperand, OperationTarget::ADH);
    
    class Instruction {
        private:
            Byte opcode;
            std::vector<Operation> operations;
        public:
            Instruction(Byte opc, std::initializer_list<Operation> ops)
                : opcode(opc), operations(ops) {}
    
            Byte getOpcode() const { return opcode; }
            const std::vector<Operation>& getOperations() const { return operations; }
    };

    const Instruction RESET_SIGNAL = Instruction(
        0x00, // RESET
        { RESET }
    );

    const Instruction LDA_IMMEDIATE = Instruction(
        0xA9, // opcode de LDA #immediate
        { FETCH_OPCODE, FETCH_OPERAND_A }
    );
    const Instruction LDX_IMMEDIATE = Instruction(
        0xA9, // opcode de LDA #immediate
        { FETCH_OPCODE, FETCH_OPERAND_X }
    );
    const Instruction LDY_IMMEDIATE = Instruction(
        0xA9, // opcode de LDA #immediate
        { FETCH_OPCODE, FETCH_OPERAND_Y }
    );

    const std::map<Byte, Instruction> INSTRUCTION_SET = {
        { 0xA9, LDA_IMMEDIATE },
        { 0xA2, LDX_IMMEDIATE },
        { 0xA9, LDY_IMMEDIATE }
        // ...
    };
}


#endif