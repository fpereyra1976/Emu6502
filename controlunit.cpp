#include"cpu.hpp"

namespace CPU6502{

void ControlUnit::ExecuteCycle(Registers &registers, Memory &memory){
    while(1){
        switch(this->status){
            case ControlUnitStatus::FETCHING_OP_CODE: {
                try{
                    this->FetchOpCode(memory,registers);
                    auto step = this->instruction.Step(this->instructionStep);
                    this->NextStatus(step);
                }catch(CPUException &e){
                    throw CPUCyleExecutionException();
                }
          } break;
            case ControlUnitStatus::FETCHING_OPERAND: {} break;
            case ControlUnitStatus::FETCHING_MEMORY: {} break;
            case ControlUnitStatus::WRITING_MEMORY: {} break;
            case ControlUnitStatus::CHANGING_MEMORY_PG: {} break;
            case ControlUnitStatus::INDEXING_MEMORY_ADDRESS: {} break;
            case ControlUnitStatus::EXECUTE: {} break;
            default: {} break;
        }
    }
}

ControlUnitStatus ControlUnit::NextStatus(InstructionStep step){
    ControlUnitStatus result = this->status;
    switch(step){
        case InstructionStep::FETCH_OPCODE:{} break;
        case InstructionStep::FETCH_OPERAND:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;       
        case InstructionStep::CALCULATE_ADDRESS:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;  
        case InstructionStep::FETCH_ADDRESS:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;      
        case InstructionStep::FETCH_VALUE:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;     
        case InstructionStep::INCREMENT_ADDRESS_X:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break; 
        case InstructionStep::INCREMENT_ADDRESS_Y: {
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;
        case InstructionStep::FINAL_STEP:{
            result = ControlUnitStatus::FETCHING_OPERAND;
        } break;
    }
    return result;
}

Instruction ControlUnit::FetchOpCode(Memory &mem, Registers &registers){
    Byte opcode = mem.Get(registers.PC);
    auto it = this->instructions.find(opcode);
    if (it != this->instructions.end()){
        this->instruction = it->second;
    }else{
        throw CPUInvalidOpCodeExcepcion();
    }
    registers.PC++;
    registers._IR = opcode;
    this->instructionStep = 0;
    return this->instruction;
}

} // end namespace