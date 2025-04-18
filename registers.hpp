#ifndef __REGISTERS_HPP
#define __REGISTERS_HPP

#include"common.hpp"

namespace CPU6502{   

class Registers{
    public:
    Byte    _IR;
    Byte    _TMP;
    Byte    _ADL;
    Byte    _ADH;
    Byte    _DL;
    Byte    _BL;
    Byte    A;
    Byte    X;
    Byte    Y;
    Byte    P;
    Word    SP;
    Word    PC;
};

}
#endif