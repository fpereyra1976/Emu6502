#include"cpu.hpp"

namespace CPU6502{

void ControlUnit::ExecuteCycle(Registers &registers, Memory &memory){
    while(1){
        switch(this->status){
            case ControlUnitStatus::FETCHING_OP_CODE: {} break;
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
} // end namespace