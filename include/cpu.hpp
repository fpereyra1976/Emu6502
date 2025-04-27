#ifndef __CPU_HPP_
#define __CPU_HPP_

#include<map>

#include"common.hpp"
#include"memory.hpp"
#include"instructions.hpp"
#include"exceptions.hpp"

namespace CPU6502{   
    using InstructionSet = std::map<Byte, Instruction>;

    enum class ControlUnitStatus : uint8_t { 
        FETCHING_OP_CODE        =   0x01, 
        FETCHING_OPERAND        =   0x02, 
        // FETCHING_OPERAND_VALUE  =   0x04, 
        // FETCHING_MEMORY         =   0x08,
        // WRITING_MEMORY          =   0x10,
        // CHANGING_MEMORY_PG      =   0x20,
        // INDEXING_MEMORY_ADDRESS =   0x40,
        // EXECUTE                 =   0x80
    };

    class CPU{
        private:
            ControlUnitStatus status;
            Memory &memory;

        public:
            Registers registers;

            CPU(Memory &memory) : status(ControlUnitStatus::FETCHING_OP_CODE), memory(memory) {}
            void Reset();
            Byte OnTick();
            Byte ExecuteCycle();
            Byte FetchOpcode();
            Byte FetchOperand(OperationTarget tg);
            
            Byte FetchOperandImmediateA();
            Byte FetchOperandImmediateX();
            Byte FetchOperandImmediateY();

            Byte FetchOperandZeropage();

            Byte FetchFirstOperandAbsolute();
            Byte FetchSecondOperandAbsolute();

            Byte FecthOperanIndirectX();
            Byte FecthOperanIndirectY();
    };
}

#endif