#ifndef __CPU_HPP_
#define __CPU_HPP_

#include<map>

#include"common.hpp"
#include"memory.hpp"
#include"instructions.hpp"


namespace CPU6502{   
    using InstructionSet = std::map<Byte, Instruction>;
    
    class CPUException :  public std::exception{
        public:
        const char* what() const noexcept override {
            return "CPUException";
         }
    };

    class CPUInvalidOpCodeExcepcion : public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUInvalidOpCodeExcepcion";
         }
    };

    class CPUCyleExecutionException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCyleExecutionException";
         }
    };

    class CPUCInvalidInstructionTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCInvalidInstructionTypeException";
         }
    };

    class CPUCOnTickException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUCOnTickException";
         }
    };

    class CPUInvalidInstructionTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUInvalidInstructionTypeException";
         }
    };

    class CPUNoOperandsImplicitTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUNoOperandsImplicitTypeException";
         }
    };

    class CPUNoFetchValueOnInmediatTypeException: public CPUException {
        public:
        const char* what() const noexcept override {
            return "CPUNoFetchValueOnInmediatTypeException";
         }
    };

    class Registers{
        public:
        Byte    _IR;
        Byte    _TMP;
        Byte    _ADL;
        Byte    _ADH;
        Byte    _DL;
        Byte    _BL;
        Byte    A;
        Byte    X;
        Byte    Y;
        Byte    P;
        Word    SP;
        Word    PC;
    };
    
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
            Byte FetchOpCode(Memory &mem, Registers &registers){
                return Byte(0x00;)
            }
            Byte FetchOperand(Memory &mem, Registers &registers){
                return Byte(0x00;)
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
            int OnTick(){
                try{
                    this->controlUnit.ExecuteCycle(this->registers,this->memory);
                }catch(CPUException &e){
                    throw CPUCOnTickException();
                }
                return 0; // TODO
            }
    };

}

#endif