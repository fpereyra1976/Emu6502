#include <gtest/gtest.h>
#include "cpu.hpp"

TEST(CPU, FetchOpcode) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Word pc = CPU6502::Byte(0x0000);
    CPU6502::Byte nop = CPU6502::Byte(0xEA);
    CPU6502::Word address = CPU6502::Word(0x0000);

    memory.Set(address,nop);  // NOP Operation

    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = pc;

    CPU6502::Byte opcode = cpu.FetchOpcode();

    // Check Result
    EXPECT_EQ(opcode, 0xea);

    // Check every register
    EXPECT_EQ(cpu.registers._AB,0x0000);
    EXPECT_EQ(cpu.registers._DB,0xea);
    EXPECT_EQ(cpu.registers._IR,0xea);
    EXPECT_EQ(cpu.registers.PC,pc+1);
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
    EXPECT_EQ(cpu.registers.A,0x00);
    EXPECT_EQ(cpu.registers.X,0x00);
    EXPECT_EQ(cpu.registers.Y,0x00);
    EXPECT_EQ(cpu.registers._ADH,0x00);
    EXPECT_EQ(cpu.registers._ADL,0x00);
    EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU, FetchOperandImmediateA) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte value = CPU6502::Byte(0xAA);
    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte result = cpu.FetchOperandImmediateA();

     // Check Result
     EXPECT_EQ(result, value);

     // Check every register
     EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
     EXPECT_EQ(cpu.registers._AB,address);
     EXPECT_EQ(cpu.registers._DB,value);
     EXPECT_EQ(cpu.registers.PC,address+1);
     EXPECT_EQ(cpu.registers.A,value);

     // No Modified
     EXPECT_EQ(cpu.registers._IR,0x00);
     EXPECT_EQ(cpu.registers.X,0x00);
     EXPECT_EQ(cpu.registers.Y,0x00);
     EXPECT_EQ(cpu.registers._ADH,0x00);
     EXPECT_EQ(cpu.registers._ADL,0x00);
     EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU, FetchOperandImmediateX) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte value = CPU6502::Byte(0xAA);
    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte result = cpu.FetchOperandImmediateX();

     // Check Result
    EXPECT_EQ(result, value);

    // Check every register
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
    EXPECT_EQ(cpu.registers._AB,address);
    EXPECT_EQ(cpu.registers._DB,value);
    EXPECT_EQ(cpu.registers.PC,address+1);
    EXPECT_EQ(cpu.registers.X,value);


    // No Modified
    EXPECT_EQ(cpu.registers._IR,0x00);
    EXPECT_EQ(cpu.registers.A,0x00);
    EXPECT_EQ(cpu.registers.Y,0x00);
    EXPECT_EQ(cpu.registers._ADH,0x00);
    EXPECT_EQ(cpu.registers._ADL,0x00);
    EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU, FetchOperandImmediateY) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte value = CPU6502::Byte(0xAA);
    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte result = cpu.FetchOperandImmediateY();

     // Check Result
     EXPECT_EQ(result, value);

     // Check every register
     EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
     EXPECT_EQ(cpu.registers._AB,address);
     EXPECT_EQ(cpu.registers._DB,value);
     EXPECT_EQ(cpu.registers.PC,address+1);
     EXPECT_EQ(cpu.registers.Y,value);


     // No Modified
     EXPECT_EQ(cpu.registers._IR,0x00);
     EXPECT_EQ(cpu.registers.A,0x00);
     EXPECT_EQ(cpu.registers.X,0x00);
     EXPECT_EQ(cpu.registers._ADH,0x00);
     EXPECT_EQ(cpu.registers._ADL,0x00);
     EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU,FetchOperandZeropage) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte value = CPU6502::Byte(0xAB);
    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte tmp_lo = cpu.FetchOperandZeropage();

    // Check Result
    EXPECT_EQ(tmp_lo, value);

    // Check every register
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
    EXPECT_EQ(cpu.registers._AB,address);
    EXPECT_EQ(cpu.registers._DB,value);
    EXPECT_EQ(cpu.registers.PC,address+1);
    EXPECT_EQ(cpu.registers._ADL,value);   

    // No Modified
    EXPECT_EQ(cpu.registers._IR,0x00);
    EXPECT_EQ(cpu.registers.A,0x00);
    EXPECT_EQ(cpu.registers.X,0x00);
    EXPECT_EQ(cpu.registers.Y,0x00);
    EXPECT_EQ(cpu.registers._ADH,0x00);
    EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU,FetchFirstOperandAbsolute) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte value = CPU6502::Byte(0xAB);
    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte tmp_lo = cpu.FetchFirstOperandAbsolute();

    // Check Result
    EXPECT_EQ(tmp_lo, value);

    // Check every register
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
    EXPECT_EQ(cpu.registers._AB,address);
    EXPECT_EQ(cpu.registers._DB,value);
    EXPECT_EQ(cpu.registers.PC,address+1);
    EXPECT_EQ(cpu.registers._ADL,value);   

    // No Modified
    EXPECT_EQ(cpu.registers._IR,0x00);
    EXPECT_EQ(cpu.registers.A,0x00);
    EXPECT_EQ(cpu.registers.X,0x00);
    EXPECT_EQ(cpu.registers.Y,0x00);
    EXPECT_EQ(cpu.registers._ADH,0x00);
    EXPECT_EQ(cpu.registers.SP,0x0100);
}

TEST(CPU,FetchSecondOperandAbsolute){
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte lo_value = CPU6502::Byte(0x34);
    CPU6502::Byte hi_value = CPU6502::Byte(0x12);

    CPU6502::Word address = CPU6502::Word(0x0001);
    memory.Set(address,lo_value);  // Ser Value
    memory.Set(address+1,hi_value);  // Ser Value
    
    // Remove when reset method is completed
    cpu.registers._TMP  = 0x0000;
    cpu.registers._AB   = 0x0000;
    cpu.registers._DB   = 0x00;
    cpu.registers._IR   = 0x00;
    cpu.registers._ADL  = 0x00;
    cpu.registers._ADH  = 0x00;
    cpu.registers._RW   = CPU6502::Bit::On;
    cpu.registers.A     = 0x00;
    cpu.registers.X     = 0x00;
    cpu.registers.Y     = 0x00;
    cpu.registers.SP    = 0x100;
    cpu.registers.PC    = address;

    CPU6502::Byte tmp_lo = cpu.FetchFirstOperandAbsolute();
    CPU6502::Byte tmp_hi = cpu.FetchSecondOperandAbsolute();

    // Check Result
    EXPECT_EQ(tmp_lo, lo_value);
    EXPECT_EQ(tmp_hi, hi_value);

    // Check every register
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
    EXPECT_EQ(cpu.registers._AB,address+1);
    EXPECT_EQ(cpu.registers._DB,hi_value);
    EXPECT_EQ(cpu.registers.PC,address+2);
    EXPECT_EQ(cpu.registers._ADH,hi_value);
    EXPECT_EQ(cpu.registers._TMP,(hi_value<<8)|lo_value);   

    // No Modified
    EXPECT_EQ(cpu.registers._IR,0x00);
    EXPECT_EQ(cpu.registers.A,0x00);
    EXPECT_EQ(cpu.registers.X,0x00);
    EXPECT_EQ(cpu.registers.Y,0x00);
    EXPECT_EQ(cpu.registers.SP,0x0100);
}