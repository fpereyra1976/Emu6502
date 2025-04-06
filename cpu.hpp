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


    class Registers{
        public:
        Byte    _IR;
        Byte    _TMP;
        Byte    _ADL;
        Byte    _ADH;
        Byte    _DL;
        Byte    A;
        Byte    X;
        Byte    Y;
        Byte    P;
        Word    SP;
        Word    PC;
    };
    
    enum class ControlUnitStatus : uint8_t { 
        FETCHING_OP_CODE        =   0x01, 
        FETCHING_OPERAND        =   0x02, 
        FETCHING_MEMORY         =   0x04, 
        WRITING_MEMORY          =   0x08,
        CHANGING_MEMORY_PG      =   0x16,
        INDEXING_MEMORY_ADDRESS =   0x32,
        EXECUTE                 =   0x64
    };


    class ControlUnit{
        private:
            ControlUnitStatus status;
            Instruction instruction;
            Byte instructionStep;
            InstructionSet instructions;
            
        public:
            ControlUnit(){
                this->status = ControlUnitStatus::FETCHING_OP_CODE;
                this->instruction = INS_NOP_INSTRUCTION_IMPLICIT;
                this->instructionStep = 0;
                this->instructions = {
                    {INS_NOP_INSTRUCTION_IMPLICIT.Code(),INS_NOP_INSTRUCTION_IMPLICIT},
                    {INS_LDA_INSTRUCTION_INMEDIATE.Code(),INS_LDA_INSTRUCTION_INMEDIATE},
                    {INS_LDA_INSTRUCTION_ZEROPAGE.Code(),INS_LDA_INSTRUCTION_ZEROPAGE},
                    {INS_LDA_INSTRUCTION_ZEROPAGE_INDEX_X.Code(),INS_LDA_INSTRUCTION_ZEROPAGE_INDEX_X},
                    {INS_LDA_INSTRUCTION_ABSOLUTE.Code(),INS_LDA_INSTRUCTION_ABSOLUTE},
                    {INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_X.Code(),INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_X},
                    {INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_Y.Code(),INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_Y},
                    {INS_LDA_INSTRUCTION_INDIRECT_INDEX_X.Code(),INS_LDA_INSTRUCTION_INDIRECT_INDEX_X},
                    {INS_LDA_INSTRUCTION_INDIRECT_INDEX_Y.Code(),INS_LDA_INSTRUCTION_INDIRECT_INDEX_Y}
                };
            }        
            Instruction FetchOpCode(Memory &mem, Registers &registers);
            ControlUnitStatus NextStatus(InstructionStep step);
            void ExecuteCycle(Registers &registers, Memory &memory);
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