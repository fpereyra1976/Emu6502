#ifndef __INSTRUCTION_HPP_
#define __INSTRUCTION_HPP_

#include<vector>
#include <initializer_list>

namespace CPU6502{
    const Byte OP_CODE_INSTRUCTION_NOP_IMP  = 0xEA;
    const Byte OP_CODE_INSTRUCTION_LDA_INM  = 0xA9;
    const Byte OP_CODE_INSTRUCTION_LDA_ZPG  = 0xA5;
    const Byte OP_CODE_INSTRUCTION_LDA_ZIX  = 0xB5;
    const Byte OP_CODE_INSTRUCTION_LDA_ABS  = 0xAD;
    const Byte OP_CODE_INSTRUCTION_LDA_AIX  = 0xBD;
    const Byte OP_CODE_INSTRUCTION_LDA_AIY  = 0xB9;
    const Byte OP_CODE_INSTRUCTION_LDA_INX  = 0xA1;
    const Byte OP_CODE_INSTRUCTION_LDA_INY  = 0xB1;


    void nop_implicit(std::initializer_list<Byte> args);

    void lda_inmediate(std::initializer_list<Byte> args);
    void lda_zeropage(std::initializer_list<Byte> args);
    void lda_zeropage_index_x(std::initializer_list<Byte> args);
    void lda_absolute(std::initializer_list<Byte> args);
    void lda_absolute_index_x(std::initializer_list<Byte> args);
    void lda_absolute_index_y(std::initializer_list<Byte> args);
    void lda_indirect_index_x(std::initializer_list<Byte> args);
    void lda_indirect_index_y(std::initializer_list<Byte> args);

    enum class Operands : uint8_t { CERO = 0, ONE = 1, TWO = 2, THREE = 3 };

    enum class InstructionType : uint16_t { 
        IMPLICIT    = 0x0000, 
        INMEDIAT    = 0x0001,
        ZEROPAGE    = 0x0002,
        ZEROPAGE_X  = 0x0004, 
        ABSOLUTE    = 0x0008,
        ABSOLUTE_X  = 0x0016,
        ABSOLUTE_Y  = 0x0032,
        INDIRECT_X  = 0x0064,
        INDIRECT_Y  = 0x0128,
    };

    enum class InstructionStep : uint16_t { 
        FETCH_OPCODE        = 0x0001, 
        FETCH_OPERAND       = 0x0002, 
        CALCULATE_ADDRESS   = 0x0004, 
        FETCH_ADDRESS       = 0x0008, 
        FETCH_VALUE         = 0x0016,
        INCREMENT_ADDRESS_X = 0x0032,
        INCREMENT_ADDRESS_Y = 0x0064,
        FINAL_STEP          = 0x0128
    };

    using Function = void (*)(std::initializer_list<Byte> args);
    using StepsVector = std::vector<InstructionStep>;

    class Instruction {
        private:
            Byte            op_code;
            InstructionType type;
            Function        func;
            StepsVector     steps;
        
        public:
            Instruction(){
                // Por defecto definimos la instrucción como NOP 0xea
                this->op_code = OP_CODE_INSTRUCTION_NOP_IMP;
                this->type = InstructionType::IMPLICIT;
                this->func = nop_implicit;
                this->steps = {InstructionStep::FINAL_STEP}; 
            }

            Instruction(Byte op_code,Function func,InstructionType type,StepsVector steps){
                this->op_code = op_code;
                this->func = func;
                this->type = type;
                this->steps = steps;
            }

            void Execute(std::initializer_list<Byte> args) {        
                // Llamar a la función con los argumentos
                this->func(args);
            }

            Byte Code() const{
                return this->op_code;
            }

            InstructionStep Step(u_int8_t idx){
                try {
                    InstructionStep step = this->steps.at(idx);
                    return  step;
                } 
                catch (const std::out_of_range& e) {
                    return InstructionStep::FINAL_STEP;
                }     
            }

            InstructionType Type(){
                return this->type;
            }

    };
    

    const Instruction INS_NOP_INSTRUCTION_IMPLICIT  = Instruction(OP_CODE_INSTRUCTION_NOP_IMP,nop_implicit,InstructionType::IMPLICIT,{
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_INMEDIATE = Instruction(OP_CODE_INSTRUCTION_LDA_INM,lda_inmediate,InstructionType::INMEDIAT,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_ZEROPAGE  = Instruction(OP_CODE_INSTRUCTION_LDA_ZPG,lda_zeropage,InstructionType::ZEROPAGE,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_ZEROPAGE_INDEX_X  = Instruction(OP_CODE_INSTRUCTION_LDA_ZIX,lda_zeropage_index_x,InstructionType::ZEROPAGE_X,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::INCREMENT_ADDRESS_X,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_ABSOLUTE  = Instruction(OP_CODE_INSTRUCTION_LDA_ABS,lda_absolute,InstructionType::ABSOLUTE,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_X  = Instruction(OP_CODE_INSTRUCTION_LDA_AIX,lda_absolute_index_x,InstructionType::ABSOLUTE_X,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_OPERAND,
        InstructionStep::INCREMENT_ADDRESS_X,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP

    });
    const Instruction INS_LDA_INSTRUCTION_ABSOLUTE_INDEX_Y  = Instruction(OP_CODE_INSTRUCTION_LDA_AIY,lda_absolute_index_y,InstructionType::ABSOLUTE_Y,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_OPERAND,
        InstructionStep::INCREMENT_ADDRESS_Y,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP
    }); 
    const Instruction INS_LDA_INSTRUCTION_INDIRECT_INDEX_X  = Instruction(OP_CODE_INSTRUCTION_LDA_INX,lda_indirect_index_x,InstructionType::INDIRECT_X,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::INCREMENT_ADDRESS_X,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP
    }); 
    const Instruction INS_LDA_INSTRUCTION_INDIRECT_INDEX_Y  = Instruction(OP_CODE_INSTRUCTION_LDA_INY,lda_indirect_index_y,InstructionType::INDIRECT_Y,{
        InstructionStep::FETCH_OPERAND,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::INCREMENT_ADDRESS_Y,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::FETCH_ADDRESS,
        InstructionStep::FETCH_VALUE,
        InstructionStep::FINAL_STEP
    });
};
#endif