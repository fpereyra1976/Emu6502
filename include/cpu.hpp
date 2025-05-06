#ifndef __CPU_HPP_
#define __CPU_HPP_

#include<map>

#include"common.hpp"
#include"memory.hpp"
#include"instructions.hpp"
#include"exceptions.hpp"

namespace CPU6502{   
    using InstructionSet = std::map<Byte, Instruction>;

    class CPU{
        private:
            OperationStep state;
            InstructionSet instructionSet;
            Memory &memory;
            bool clockState;

            OperarionStepsSequenceIterator operarionStepsSequenceIterator;

            Byte FetchAddressZeropage_(Byte idx);
        public:
            Registers registers;

            CPU(Memory &memory,const InstructionSet i=INSTRUCTION_SET) : 
                state(OperationStep::Reset), 
                instructionSet(i), 
                memory(memory), 
                clockState(false) {}

            void Start();
            Byte ExecuteCycle();

            void Reset();
            void DoNothing();

            // Fetch Opcode common for all addressing modes
            Byte FetchOpcode();

            // Fetch Operands only Inmediate get value in same step
            Byte FetchOperandImmediate();

            Byte FetchOperandZeropage();

            Byte FetchFirstOperandAbsolute();
            Byte FetchSecondOperandAbsolute();

            Byte FecthOperanIndirect();

            // Fetch Address
            Byte FetchAddressZeropageX();
            Byte FetchAddressZeropageY();

            // Fetch Values once two operands are fetched
            Byte FetchValueAbsolute();

            // Fetch Values once one operand is fetched
            Byte FetchValueZeropage();

            // Fetch Values once one operand is fetched
            Byte FetchValueZeropageIndexed(); // Depends on FetchAddressZeropage

            void UpdateFlags();
    };
}
#endif