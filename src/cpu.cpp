#include<iostream>

#include"cpu.hpp"



namespace CPU6502{
 Byte CPU::Reset(){
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
     this->registers._RW = Bit::On;
     std::cout << "registers._RW: " << std::hex << this->registers._RW << std::endl;
     this->registers._AB = this->registers.PC;
     std::cout << "registers.PC: " << std::hex << this->registers.PC << std::endl;
     std::cout << "registers._AB: " << std::hex << this->registers._AB << std::endl;

     this->registers._DB = this->memory.Get(registers._AB);
     std::cout << "registers._DB: " << this->registers._DB << std::endl;

     this->registers._IR = this->registers._DB;
     std::cout << "registers._IR: " << std::hex << this->registers._IR << std::endl;

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

 Byte CPU::FetchOperandImmediate(){
    return this->FetchOperand(OperationTarget::Nil);
 }

 Byte CPU::FetchOperandZeropage(){
    return this->FetchOperand(OperationTarget::ADL);
 }

 Byte CPU::FetchOperandZeropageX(){
    return this->FetchOperand(OperationTarget::ADL);
 }

 Byte CPU::FetchOperandZeropageY(){
    return this->FetchOperand(OperationTarget::ADL);
 }

 Byte CPU::FetchFirstOperandAbsolute(){
    return this->FetchOperand(OperationTarget::ADL);
 }
 
 Byte CPU::FetchSecondOperandAbsolute(){
    return this->FetchOperand(OperationTarget::ADH);
 }
 
 Byte CPU::FetchFirstOperandAbsoluteX(){
    return this->FetchOperand(OperationTarget::ADL);
 }
 
 Byte CPU::FetchSecondOperandAbsoluteX(){
    return this->FetchOperand(OperationTarget::ADH);
 }
 
 Byte CPU::FetchFirstOperandAbsoluteY(){
    return this->FetchOperand(OperationTarget::ADL);
 }
 
 Byte CPU::FetchSecondOperandAbsoluteY(){
    return this->FetchOperand(OperationTarget::ADH);
 }
 
 Byte CPU::FecthOperanIndirectX(){
    return this->FetchOperand(OperationTarget::ADL);

 }

 Byte CPU::FecthOperanIndirectY(){
    return this->FetchOperand(OperationTarget::ADL);
 }

} // end namespace