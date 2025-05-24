#ifndef __MEMORY_HPP_
#define __MEMORY_HPP_

#include"common.hpp"

namespace CPU6502{ 
    const Word MEMORY_SIZE = 0xffff;
    class Memory {
        private:
            std::array<Byte, MEMORY_SIZE+1> data;
    
        public:
            Memory(){  
                this->Initialise();
            }

            Byte &Read(Word p){
                return this->data[p];
            }

            const Byte& Read(Word p) const {
                return this->data[p];
            }
            
            void Write(Word p,Byte &v){
                // No validation needed. (?)
                this->data[p] = v;
            }

            void Initialise(){
                data.fill(0);  // Inicializa todo el array con 0.

                // Reset Vector
                data[0xfffc] = 0x00;
                data[0xfffd] = 0x08;
                data[0x0801] = 0xa9; data[0x0802] = 0x80;   // LDA #$80
                data[0x0803] = 0x69; data[0x0804] = 0x08;   // ADC #$08
            }

            // Lectura y escritura
            Byte& operator[](Word p) {
                return Read(p);
            }

            // Solo lectura (si el objeto es const)
            const Byte& operator[](Word p) const {
                return Read(p);
            }
    };
};

#endif