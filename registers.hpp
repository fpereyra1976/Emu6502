#ifndef __REGISTERS_HPP
#define __REGISTERS_HPP

#include"common.hpp"

namespace CPU6502{   

class Registers{
    public:
    Word    _TMP;
    Word    _AB;
    Byte    _DB;
    Byte    _IR;
    Byte    _ADL;
    Byte    _ADH;
    Bit     _RW;
    Byte    A;
    Byte    X;
    Byte    Y;
    Byte    P;
    Word    SP;
    Word    PC;
};
}
#endif