#ifndef __CPU_HPP_
#define __CPU_HPP_

#include<map>

#include"common.hpp"
#include"memory.hpp"
#include"instructions.hpp"
#include"exceptions.hpp"


namespace CPU6502{   
    using InstructionSet = std::map<Byte, Instruction>;

    enum class RegisterOperation : Byte {
        A   = 0x01,
        X   = 0x02,
        Y   = 0x08,
        TMP = 0x10,
        ADL = 0x20,
        ADH = 0x40
    };
    
    enum class ControlUnitStatus : uint8_t { 
        FETCHING_OP_CODE        =   0x01, 
        FETCHING_OPERAND        =   0x02, 
        FETCHING_OPERAND_VALUE  =   0x04, 
        FETCHING_MEMORY         =   0x08,
        WRITING_MEMORY          =   0x10,
        CHANGING_MEMORY_PG      =   0x20,
        INDEXING_MEMORY_ADDRESS =   0x40,
        EXECUTE                 =   0x80
    };

    class ControlUnit{
        private:
            ControlUnitStatus status;
            
        public:
            ControlUnit(){
                this->status = ControlUnitStatus::FETCHING_OP_CODE;
            }        
            Byte ExecuteCycle(Memory &memory, Registers & registers);
            
            Byte FetchOpcode(Memory &memory, Registers &registers){
                registers._RW = Bit::Off;
                registers._AB = registers.PC;
                registers._DB = memory.Get(registers._AB);
                registers._IR = registers._DB;
                registers.PC++;
                return  registers._IR;
            }

            Byte FetchOperand(Memory &memory, Registers &registers,RegisterOperation ro){
                registers._RW = Bit::Off;
                registers._AB = registers.PC;
                registers._DB = memory.Get(registers._AB);
                switch(ro){
                    case RegisterOperation::A:{
                        // Immediate
                        registers.A = registers._DB;
                    } break;
                    case RegisterOperation::X:{
                        // Immediate
                        registers.Y = registers._DB;
                    } break;
                    case RegisterOperation::Y:{
                        // immediate
                        registers.Y = registers._DB;
                    } break;
                    case RegisterOperation::TMP:{}
                        registers._TMP = (0x00 << 8 ) | registers._DB;
                    break;
                    case RegisterOperation::ADL:{}
                        // Zeropage, Absolute, Indirect
                        registers._ADL = registers._DB;
                        registers._TMP = (0x00 << 8 ) | registers._DB;
                    break;
                    case RegisterOperation::ADH:{}
                        // Absolute
                        registers._ADH = registers._DB;
                        registers._TMP = (registers._ADH << 8)|registers._ADL;
                    break;
                    defaul: {}break;
                }
                registers.PC++;
                return registers._DB;
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