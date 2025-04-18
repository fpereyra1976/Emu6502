#ifndef __CPU_HPP_
#define __CPU_HPP_

#include<map>

#include"common.hpp"
#include"memory.hpp"
#include"instructions.hpp"
#include"exceptions.hpp"


namespace CPU6502{   
    using InstructionSet = std::map<Byte, Instruction>;
    
    enum class ControlUnitStatus : uint16_t { 
        FETCHING_OP_CODE        =   0x0001, 
        FETCHING_OPERAND        =   0x0002, 
        FETCHING_OPERAND_VALUE  =   0x0004, 
        FETCHING_MEMORY         =   0x0008,
        WRITING_MEMORY          =   0x0016,
        CHANGING_MEMORY_PG      =   0x0032,
        INDEXING_MEMORY_ADDRESS =   0x0064,
        EXECUTE                 =   0x0128
    };

    class ControlUnit{
        private:
            ControlUnitStatus status;
            
        public:
            ControlUnit(){
                this->status = ControlUnitStatus::FETCHING_OP_CODE;
            }        
            Byte ExecuteCycle(Memory &mem, Registers & registers);
            
            Byte FetchOpCode(Memory &mem, Registers &registers){
                return Byte(0x00);
            }
            Byte FetchOperand(Memory &mem, Registers &registers){
                return Byte(0x00);
            }
    };

    class CPU{
        private:
            ControlUnit controlUnit;
            Registers registers;
            Memory memory;

        public:
            CPU(Memory &memory){
                this->memory = memory;
            }

            void Reset(){
            }

            Byte OnTick(){
                try{
                    // Byte ExecuteCycle(Memory &mem, Registers & registers){
                    Byte b = this->controlUnit.ExecuteCycle(this->memory,this->registers);
                    return b;
                }catch(CPUException &e){
                    throw CPUCOnTickException();
                }
                return Byte(0); // TODO
            }
    };

}

#endif