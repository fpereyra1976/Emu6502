#ifndef __INSTRUCTION_HPP_
#define __INSTRUCTION_HPP_

#include<vector>
#include <initializer_list>

namespace CPU6502{
    class Executer{   
        public:
        virtual Byte FetchOpCode(Registers &regs,Memory &mem){
            Byte opcode = mem.Get(regs.PC);
        }

        virtual Byte FetchOperand(Registers &regs,Memory &mem){
            return Byte(0);
        }
    };

    class ImplicitExecuter :public Executer{
        public:
        virtual Byte FetchOperand(Registers &regs,Memory &mem){
            throw CPUInstructionInvalidOperation();
            return Byte(0);
        }
    }

    class InmediatExcecuter :public Executer{
        public:
        virtual Byte FetchOperand(Registers &regs,Memory &mem){
            regs._TMP = mem.Get(regs.PC);
            return Byte(0);
        }
    }
};
#endif