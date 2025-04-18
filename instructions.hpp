#ifndef __INSTRUCTION_HPP_
#define __INSTRUCTION_HPP_

#include<vector>
#include <initializer_list>

#include "common.hpp"
#include "registers.hpp"
#include "exceptions.hpp"
#include "memory.hpp"

namespace CPU6502{
    class Instruction {
        private:
            Byte opcode;
    };
};
#endif