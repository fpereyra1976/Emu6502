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

Byte CPU::FetchOperandImmediate(Byte &reg){
    // AB ← PC, DB ← [PC], REG ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);
  
    // The next line is only for lda/ldx/ldy (for now)
    // this line and flags updates should be moved to an specific function.
    reg = this->registers._DB;
    
    
    this->registers.PC++;

    return this->registers._DB;
}

Byte CPU::FetchOperandImmediateA(){
    return this->FetchOperandImmediate(this->registers.A);
}

Byte CPU::FetchOperandImmediateX(){
    return this->FetchOperandImmediate(this->registers.X);
}

Byte CPU::FetchOperandImmediateY(){
    return this->FetchOperandImmediate(this->registers.Y);
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

Byte CPU::FecthOperanIndirect(){
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

Byte CPU::FetchAddressZeropage(Byte idx){
    // tmp ← (tmp + idx) & $FF, AB ← tmp
    // LDA $AA,X => idx = X
    // LDX $AA,Y => idx = Y
    // LDY $AA,X => idx = X
    this->registers._TMP = (this->registers._TMP + idx ) & 0x00ff;
    this->registers._AB = this->registers._TMP;
    return this->registers._AB;
}

Byte CPU::FetchValueZeropage(Byte &reg){
    // AB ← tmp, DB ← [AB], reg ← DB
    // LDA $AA => reg = A
    // LDX $AA => reg = X
    // LDY $AA => reg = Y
    this->registers._RW = CPU6502::Bit::On;
    this->registers._AB = this->registers._TMP;

    Byte value = this->memory.Get(this->registers._AB);

    this->registers._DB = value;
    reg = this->registers._DB;

    return this->registers._DB;
}

Byte CPU::FetchValueZeropageIndexed(Byte &reg){
    // DB ← [AB], A ← DB
    this->registers._DB = this->memory.Get(this->registers._AB);
    reg = this->registers._DB;
    return this->registers._DB;
}


// Just temporary to avoid lossing this code
void CPU::UpdateFlags(){
    // Update Flags
    (this->registers.X == 0x00) ? 
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::Z): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::Z);

    (this->registers.X & 0x80) ?
        this->registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::N): 
        this->registers.P &= ~static_cast<std::uint8_t>(CPU6502::StatusFlag::N);
}

} // end namespace