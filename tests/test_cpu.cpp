#include <gtest/gtest.h>
#include "cpu.hpp"

TEST(CPU, FetchOpcode) {
    // Given
    CPU6502::Memory memory;
    CPU6502::CPU cpu(memory);

    memory[0x0000] = 0xea;  // NOP Operation
    cpu.registers.PC = 0x00;
 
    std::cout << "Fetched opcode: " << std::endl;  // Debugging inpunt
    CPU6502::Byte opcode = cpu.FetchOpcode();
    std::cout << "Fetched opcode: " << std::hex << (int)opcode << std::dec << std::endl;  // Debugging output

    EXPECT_EQ(opcode, 0xea);
}

