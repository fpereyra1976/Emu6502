#include<iostream>
#include <cstdarg>

#include"memory.hpp"
#include"cpu.hpp"

//Define computer class

int main(){
    CPU6502::Memory mem;
    CPU6502::CPU cpu(mem);
    cpu.Start();
}