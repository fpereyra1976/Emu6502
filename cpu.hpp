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
            Registers registers;
            Memory memory;

        public:
            CPU(Memory &memory){
                this->memory = memory;
            }

            Byte Reset(){
                this->registers._IR = 0x00;
                this->registers._RW = Bit::On; // READ

                this->registers._AB = 0xfffc;
                this->registers._DB = this->memory.Get(this->registers._AB);
                this->registers._ADL = this->registers._DB;

                this->registers._AB = 0xfffd;
                this->registers._DB = this->memory.Get(this->registers._AB);
                this->registers._ADH = this->registers._DB;

                this->registers._AB = (this->registers._ADH << 8) | this->registers._ADL;
                this->registers._DB = this->memory.Get(this->registers._AB);
                this->registers.PC = this->registers._DB;
                
                return 0x00;
            }

            Byte OnTick(){
                try{
                    Byte b = this->ExecuteCycle();
                    return b;
                }catch(CPUException &e){
                    throw CPUCOnTickException();
                }
                return Byte(0); // TODO
            }

            Byte ExecuteCycle(){
                while(1){
                    switch(this->status){
                        case ControlUnitStatus::FETCHING_OP_CODE: {} break;
                        case ControlUnitStatus::FETCHING_OPERAND: {} break;
                        // case ControlUnitStatus::FETCHING_MEMORY: {} break;
                        // case ControlUnitStatus::WRITING_MEMORY: {} break;
                        // case ControlUnitStatus::CHANGING_MEMORY_PG: {} break;
                        // case ControlUnitStatus::INDEXING_MEMORY_ADDRESS: {} break;
                        // case ControlUnitStatus::EXECUTE: {} break;
                        // default: {} break;
                    }
                }
                return Byte(0);
            }
            
            Byte FetchOpcode(){
                this->registers._RW = Bit::On;
                this->registers._AB = this->registers.PC;
                this->registers._DB = this->memory.Get(registers._AB);
                this->registers._IR = this->registers._DB;
                this->registers.PC++;
                return  this->registers._IR;
            }

            Byte FetchOperand(OperationTarget tg){
                this->registers._RW = Bit::On;
                this->registers._AB = this->registers.PC;
                this->registers._DB = this->memory.Get(registers._AB);
                switch(tg){
                    case OperationTarget::Nil:{
                        // To Do May not be used
                    } break;
                    case OperationTarget::A:{
                        // Immediate
                        this->registers.A = this->registers._DB;
                    } break;
                    case OperationTarget::X:{
                        // Immediate
                        this->registers.X = this->registers._DB;
                    } break;
                    case OperationTarget::Y:{
                        // immediate
                        this->registers.Y = this->registers._DB;
                    } break;
                    case OperationTarget::TMP:{}
                        // To Do May not be used
                        this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
                    break;
                    case OperationTarget::ADL:{}
                        // Zeropage, Absolute, Indirect
                        this->registers._ADL = registers._DB;
                        this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
                    break;
                    case OperationTarget::ADH:{}
                        // Absolute
                        this->registers._ADH = this->registers._DB;
                        this->registers._TMP = (this->registers._ADH << 8)|this->registers._ADL;
                    break;
                }
                this->registers.PC++;
                return this->registers._DB;
            }
    };

}

#endif