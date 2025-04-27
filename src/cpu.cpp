#include"cpu.hpp"

namespace CPU6502{
 void CPU::Reset(){
    this->registers._IR = 0x00;
    this->registers._RW = Bit::On; // READ
    this->registers.A     = 0x00;
    this->registers.X     = 0x00;
    this->registers.Y     = 0x00;
    this->registers._TMP  = 0x0000;
    this->registers.SP    = 0x0100;
    this->registers.P     = 0x21;

    this->registers._AB = 0xfffc;
    this->registers._DB = this->memory.Get(this->registers._AB);
    this->registers._ADL = this->registers._DB;

    this->registers._AB = 0xfffd;
    this->registers._DB = this->memory.Get(this->registers._AB);
    this->registers._ADH = this->registers._DB;

    this->registers._AB = (this->registers._ADH << 8) | this->registers._ADL;
    this->registers._DB = this->memory.Get(this->registers._AB);
    this->registers.PC = this->registers._DB;
 }

 Byte CPU::OnTick(){
    try{
       Byte b = this->ExecuteCycle();
       return b;
    }catch(CPUException &e){
       throw CPUCOnTickException();
    }
    return Byte(0); // TODO
 }

 Byte CPU::ExecuteCycle(){
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
 
Byte CPU::FetchOpcode(){
    //AB ← PC, DB ← [PC], IR ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
    
    this->registers._DB = this->memory.Get(registers._AB);

    this->registers._IR = this->registers._DB;
    this->registers.PC++;
    return  this->registers._IR;
 }

 Byte CPU::FetchOperand(OperationTarget tg){
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
        case OperationTarget::TMP:{
            // To Do May not be used
            this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
         }
        break;
        case OperationTarget::ADL:{
            // Zeropage, Absolute, Indirect
            this->registers._ADL = registers._DB;
            this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
        }
        break;
        case OperationTarget::ADH:{
            // Absolute
            this->registers._ADH = this->registers._DB;
            this->registers._TMP = (this->registers._ADH << 8)|this->registers._ADL;
         }
         break;
    }
    this->registers.PC++;
    return this->registers._DB;
}

Byte CPU::FetchOperandImmediateA(){
    // AB ← PC, DB ← [PC], A ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);
  
    this->registers.A = this->registers._DB;
    this->registers.PC++;

    // Update Flags   
    (this->registers.A == 0x00) ? 
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);

    (this->registers.A & 0x80) ?
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N);

    return this->registers._DB;
}

Byte CPU::FetchOperandImmediateX(){
    // AB ← PC, DB ← [PC], X ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);
  
    this->registers.X = this->registers._DB;
    this->registers.PC++;

    // Update Flags
    (this->registers.X == 0x00) ? 
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);

    (this->registers.X & 0x80) ?
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N);

    return this->registers._DB;
}

Byte CPU::FetchOperandImmediateY(){
    // AB ← PC, DB ← [PC], Y ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);
  
    this->registers.Y = this->registers._DB;
    this->registers.PC++;

    // Update Flags
    (this->registers.Y == 0x00) ? 
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);

    (this->registers.Y & 0x80) ?
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N);

    return this->registers._DB;
}

Byte CPU::FetchOperandZeropage(){
    // AB ← PC, DB ← [PC], tmp ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);

    this->registers._ADL = registers._DB;
    this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
    this->registers.PC++;
    return this->registers._DB;
}

Byte CPU::FetchFirstOperandAbsolute(){
    // AB ← PC, DB ← [PC], tmp_lo ← DB, PC ← PC + 1
    // Same as Zerpage
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
 
    this->registers._DB = this->memory.Get(registers._AB);
 
    this->registers._ADL = registers._DB;
    // tmp_lo
    this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
    this->registers.PC++;
    return this->registers._DB;
 }
 
Byte CPU::FetchSecondOperandAbsolute(){
    // AB ← PC, DB ← [PC], tmp_hi ← DB, `tmp ← tmp_lo, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
 
    this->registers._DB = this->memory.Get(registers._AB);
 
    this->registers._ADH = registers._DB;
    // tmp_hi
    this->registers._TMP = ((this->registers._TMP & 0x00FF) | (this->registers._ADH << 8));
    this->registers.PC++;
    return this->registers._DB;
}

Byte CPU::FecthOperanIndirectX(){
    // ptr ← (zp_base + X) & $FF, AB ← ptr, DB ← [AB], tmp_lo ← DB
    // Same as Zeropage
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
    
    this->registers._DB = this->memory.Get(registers._AB);

    this->registers._ADL = registers._DB;
    this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
    this->registers.PC++;
    return this->registers._DB;
}

Byte CPU::FecthOperanIndirectY(){
    // AB ← ptr, DB ← [AB], tmp_lo ← DB
    // Same as Zeropage
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
    
    this->registers._DB = this->memory.Get(registers._AB);

    this->registers._ADL = registers._DB;
    this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
    this->registers.PC++;
    return this->registers._DB;
}

} // end namespace