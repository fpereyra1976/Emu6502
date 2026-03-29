#ifndef __BUS_HPP
#define __BUS_HPP

#include"common.hpp"

namespace CPU6502{  
    class Bus{
        public:
            Word        address;
            Byte        data;
            Bit         rw;
            Bit         reset;
            Bit         irq;
            Bit         nmi;
            Bit         sync;
            Bit         rdy;
            Bit         clk;
            Bus() : address(0), 
                data(0), 
                rw(Bit::On), 
                reset(Bit::On), 
                irq(Bit::On), 
                nmi(Bit::On),
                sync(Bit::On),
                rdy(Bit::On),   
                clk(Bit::Off) {}
    }; 
}
#endif // __BUS_HPP