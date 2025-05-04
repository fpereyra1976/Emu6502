#include <thread>
#include <chrono>

#include"cpu.hpp"

namespace CPU6502{

void CPU::Start(){
    // Set the initial state
    this->state = OperationStep::Reset;
    while(1){
        std::this_thread::sleep_for(std::chrono::nanoseconds(500));  // 0.5 µs
        this->clockState = !this->clockState;
        if(this->clockState){
            try{
                this->ExecuteCycle();
            }catch(CPUCOnTickException &e){
                throw CPUException();
            }
        }
    }
}

Byte CPU::ExecuteCycle(){
    // This is the default state
    switch(this->state){
        case OperationStep::Reset: {
            this->Reset();
            try{
                auto &steps = this->instructionSet.at(this->registers._IR).Steps();
                this->operarionStepsSequenceIterator = steps.cbegin();
                if (this->operarionStepsSequenceIterator == steps.cend()){
                    this->state = OperationStep::FetchOpcode;
                } else{
                    ++this->operarionStepsSequenceIterator;
                    this->state = *this->operarionStepsSequenceIterator;
                } 
            }catch(const std::out_of_range& e){
                throw CPUException();
            }
        } break;
        case OperationStep::FetchOpcode: {
            this->FetchOpcode();
            try{
                auto &steps = this->instructionSet.at(this->registers._IR).Steps();
                this->operarionStepsSequenceIterator = steps.cbegin();
                if (this->operarionStepsSequenceIterator == steps.cend()){
                    this->state = OperationStep::FetchOpcode;
                }else{
                    ++this->operarionStepsSequenceIterator;
                    this->state = *this->operarionStepsSequenceIterator;  
                }
            }catch(const std::out_of_range& e){
                throw CPUException();
            }
        } break;
        case OperationStep::FetchOperand: {} break; 
        case OperationStep::FetchFirstOperand: {
            this->FetchFirstOperandAbsolute();
            try{
                auto &steps = this->instructionSet.at(this->registers._IR).Steps();
                ++this->operarionStepsSequenceIterator;
                if (this->operarionStepsSequenceIterator == steps.cend()){
                    this->state = OperationStep::FetchOpcode;
                }else{
                    this->state = *this->operarionStepsSequenceIterator;
                }
            }catch(const std::out_of_range& e){
                throw CPUException();
            }
        } break;
        case OperationStep::FetchSecondOperand: {
            this->FetchSecondOperandAbsolute();
            try{
                auto &steps = this->instructionSet.at(this->registers._IR).Steps();
                ++this->operarionStepsSequenceIterator;
                if (this->operarionStepsSequenceIterator == steps.cend()){
                    this->state = OperationStep::FetchOpcode;
                }else{
                    this->state = *this->operarionStepsSequenceIterator;
                }
            }catch(const std::out_of_range& e){
                throw CPUException();
            }
        } break;
        case OperationStep::LoadProgramCounter: {
            this->LoadProgramCounter();
            try{
                auto &steps = this->instructionSet.at(this->registers._IR).Steps();
                this->operarionStepsSequenceIterator++;
                if (this->operarionStepsSequenceIterator == steps.cend()){
                    this->state = OperationStep::FetchOpcode;
                }else{
                    this->state = *this->operarionStepsSequenceIterator;
                }
            }catch(const std::out_of_range& e){
                throw CPUException();
            }
        } break;
        case OperationStep::FetchValue: {} break; 
        case OperationStep::FetchIndexedAddress: {} break;
        case OperationStep::FetchIndexedValue: {} break;
        case OperationStep::FetchValueAbsolute: {} break;
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

void CPU::Reset(){
    this->registers.A     = 0x00;
    this->registers.X     = 0x00;
    this->registers.Y     = 0x00;
    this->registers.SP    = 0x0100;
    this->registers.P     = 0x21;
    this->registers.PC    = 0xfffc;

    this->registers._IR   = 0x00;
    this->registers._RW   = Bit::On; // READ
    this->registers._AB   = 0x0000;
    this->registers._DB   = 0x00;
    this->registers._TMP  = 0x0000;
 }

Byte CPU::FetchOperandImmediate_(Byte &reg){
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
    return this->FetchOperandImmediate_(this->registers.A);
}

Byte CPU::FetchOperandImmediateX(){
    return this->FetchOperandImmediate_(this->registers.X);
}

Byte CPU::FetchOperandImmediateY(){
    return this->FetchOperandImmediate_(this->registers.Y);
}

Byte CPU::FetchOperandZeropage(){
    // AB ← PC, DB ← [PC], tmp ← DB, PC ← PC + 1
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;

    this->registers._DB = this->memory.Get(registers._AB);

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
 
    // tmp_hi
    this->registers._TMP = ((this->registers._TMP & 0x00FF) | (registers._DB << 8));
    this->registers.PC++;
    return this->registers._DB;
}

// This method load program counter during reset process
Byte CPU::LoadProgramCounter(){
    this->registers.PC = this->registers._TMP;
    return Byte(0);
}

Byte CPU::FecthOperanIndirect(){
    // ptr ← (zp_base + X) & $FF, AB ← ptr, DB ← [AB], tmp_lo ← DB
    // Same as Zeropage
    this->registers._RW = Bit::On;
    this->registers._AB = this->registers.PC;
    
    this->registers._DB = this->memory.Get(registers._AB);

    this->registers._TMP = (0x00 << 8 ) | this->registers._DB;
    this->registers.PC++;
    return this->registers._DB;
}

Byte CPU::FetchValueAbsolute(){
    this->registers._AB = this->registers._TMP;
    return this->memory.Get(this->registers._AB);
}

Byte CPU::FetchAddressZeropageX(){
    return this->FetchAddressZeropage_(this->registers.X);
}

Byte CPU::FetchAddressZeropageY(){
    return this->FetchAddressZeropage_(this->registers.Y);
}

Byte CPU::FetchValueZeropage_(Byte &reg){
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

Byte CPU::FetchValueZeropageA(){
    return this->FetchValueZeropage_(this->registers.A);
}

Byte CPU::FetchValueZeropageX(){
    return this->FetchValueZeropage_(this->registers.X);
}

Byte CPU::FetchValueZeropageY(){
    return this->FetchValueZeropage_(this->registers.Y);
}

Byte CPU::FetchAddressZeropage_(Byte idx){
    // tmp ← (tmp + idx) & $FF, AB ← tmp
    // LDA $AA,X => idx = X
    // LDX $AA,Y => idx = Y
    // LDY $AA,X => idx = X
    this->registers._TMP = (this->registers._TMP + idx ) & 0x00ff;
    this->registers._AB = this->registers._TMP;
    return this->registers._AB;
}

Byte CPU::FetchValueZeropageIndexed_(Byte &reg){
    // DB ← [AB], A ← DB
    this->registers._DB = this->memory.Get(this->registers._AB);
    reg = this->registers._DB;
    return this->registers._DB;
}

Byte CPU::FetchValueZeropageIndexedX(){
   return FetchValueZeropageIndexed_(this->registers.X);
}

Byte CPU::FetchValueZeropageIndexedY(){
    return FetchValueZeropageIndexed_(this->registers.Y);
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