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
            Memory &memory;
            bool clockState;

            Byte FetchOperandImmediate_(Byte &reg);
            Byte FetchAddressZeropage_(Byte idx);
            Byte FetchValueZeropage_(Byte &reg);
            Byte FetchValueZeropageIndexed_(Byte &reg); // Depends on FetchAddressZeropage

        public:
            Registers registers;

            CPU(Memory &memory) : state(OperationStep::Reset), memory(memory), clockState(false) {}
            void Start();
            Byte ExecuteCycle();

            void Reset();
            // Fetch Opcode common for all addressing modes
            Byte FetchOpcode();

            // Fetch Operands only Inmediate get value in same step
            Byte FetchOperandImmediateA();
            Byte FetchOperandImmediateX();
            Byte FetchOperandImmediateY();

            Byte FetchOperandZeropage();

            Byte FetchFirstOperandAbsolute();
            Byte FetchSecondOperandAbsolute();

            Byte FecthOperanIndirect();

            // Fetch Address
            Byte FetchAddressZeropageX();
            Byte FetchAddressZeropageY();

            // Fetch Values
            Byte FetchValueAbsolute();
            Byte FetchValueZeropageA();
            Byte FetchValueZeropageX();
            Byte FetchValueZeropageY();

            Byte FetchValueZeropageIndexedX(); // Depends on FetchAddressZeropage
            Byte FetchValueZeropageIndexedY(); // Depends on FetchAddressZeropage

            Byte LoadProgramCounter();

            void UpdateFlags();
    };
}

#endif