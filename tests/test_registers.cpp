#include <gtest/gtest.h>
#include "registers.hpp"

TEST(Registers, UpdateZeroFlag) {
    CPU6502::Registers reg;
    reg.UpdateZeroFlag(0x00);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::Z), static_cast<std::uint8_t>(CPU6502::StatusFlag::Z));

    reg.UpdateZeroFlag(0x01);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::Z), 0);
}

TEST(Registers, UpdateNegativeFlag) {
    CPU6502::Registers reg;
    reg.UpdateNegativeFlag(0x80);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::N), static_cast<std::uint8_t>(CPU6502::StatusFlag::N));

    reg.UpdateNegativeFlag(0x7F);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::N), 0);
}

TEST(Registers, UpdateCarryFlag) {
    CPU6502::Registers reg;
    reg.UpdateCarryFlag(0x0100);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::C), static_cast<std::uint8_t>(CPU6502::StatusFlag::C));

    reg.UpdateCarryFlag(0x00FF);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::C), 0);
}

TEST(Registers, UpdateOverflowFlag) {
    CPU6502::Registers reg;
    reg.UpdateOverflowFlag(0x7F, 0x02, 0x81);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::O), static_cast<std::uint8_t>(CPU6502::StatusFlag::O));

    reg.UpdateOverflowFlag(0x7E, 0x01, 0x7F);
    EXPECT_EQ(reg.P & static_cast<std::uint8_t>(CPU6502::StatusFlag::O), 0);
}

