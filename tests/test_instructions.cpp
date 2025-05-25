#include <gtest/gtest.h>
#include "instructions.hpp"


TEST(Instructions, RESET) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    CPU6502::Byte result = CPU6502::Reset(registers, memory);

    // Check Result
    EXPECT_EQ(result, registers.PC);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x00);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
}

TEST(Instructions, NOP) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    CPU6502::Byte result = CPU6502::NOP(registers, memory);

    // Check Result
    EXPECT_EQ(result, 0);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x00);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
    EXPECT_EQ(registers.P, 0x00);
}

TEST(Instructions, SEC) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    CPU6502::Byte result = CPU6502::SEC(registers, memory);

    // Check Result
    EXPECT_EQ(result, 0);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x00);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
    EXPECT_EQ(registers.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::C), static_cast<std::uint8_t>(CPU6502::StatusFlag::C));
}

TEST(Instructions, CLC) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    registers.P |= static_cast<std::uint8_t>(CPU6502::StatusFlag::C); // Set carry flag
    CPU6502::Byte result = CPU6502::CLC(registers, memory);

    // Check Result
    EXPECT_EQ(result, 0);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x00);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
    EXPECT_EQ(registers.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::C), 0);
}

TEST(Instructions, LDA) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    registers._DB = 0x80; // Simulate loading value into A
    CPU6502::Byte result = CPU6502::LDA(registers, memory);

    // Check Result
    EXPECT_EQ(result, registers.A);
    EXPECT_EQ(0x80, registers.A);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x80);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
}

TEST(Instructions, LDX) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    registers._DB = 0x80; // Simulate loading value into X
    CPU6502::Byte result = CPU6502::LDX(registers, memory);

    // Check Result
    EXPECT_EQ(result, registers.X);
    EXPECT_EQ(0x80, registers.X);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x80);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.Y, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
}

TEST(Instructions, LDY) {
    CPU6502::Registers registers;
    CPU6502::Memory memory;
    registers._DB = 0x80; // Simulate loading value into Y
    CPU6502::Byte result = CPU6502::LDY(registers, memory);

    // Check Result
    EXPECT_EQ(result, registers.Y);
    EXPECT_EQ(0x80, registers.Y);
    EXPECT_EQ(registers.PC, 0x0000);
    EXPECT_EQ(registers._TMP, 0x0000);
    EXPECT_EQ(registers._RW, CPU6502::Bit::Off);
    EXPECT_EQ(registers._AB, 0x0000);
    EXPECT_EQ(registers._DB, 0x80);
    EXPECT_EQ(registers.A, 0x00);
    EXPECT_EQ(registers.X, 0x00);
    EXPECT_EQ(registers.SP, 0x0000);
}