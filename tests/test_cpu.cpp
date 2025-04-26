#include <gtest/gtest.h>
#include "cpu.hpp"

TEST(CPU, FetchOpcode) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);
    CPU6502::Byte pc = CPU6502::Byte(0x00);
    CPU6502::Byte nop = CPU6502::Byte(0xEA);
    CPU6502::Word address = CPU6502::Word(0x0000);

    memory.Set(address,nop);  // NOP Operation
    cpu.registers.PC = pc;

    CPU6502::Byte opcode = cpu.FetchOpcode();

    EXPECT_EQ(opcode, 0xea);
    EXPECT_EQ(cpu.registers._AB,0x00);
    EXPECT_EQ(cpu.registers._DB,0xea);
    EXPECT_EQ(cpu.registers._IR,0xea);
    EXPECT_EQ(cpu.registers._RW,CPU6502::Bit::On);
}

